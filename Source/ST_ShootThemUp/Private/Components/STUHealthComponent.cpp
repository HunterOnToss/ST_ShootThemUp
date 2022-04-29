// Shoot Them Up Game. All Right Reserved 2022.

#include "Components/STUHealthComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "STUUtils.h"
#include "STUGameModeBase.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

//#include "Dev/STUIceDamageType.h"
//#include "Dev/STUFireDamageType.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)

USTUHealthComponent::USTUHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool USTUHealthComponent::TryToAddHealth(float HealthAmount)
{
    if (IsDead() || IsHealthFull())
        return false;
    
    SetHealth(Health + HealthAmount);

    return true;
}

bool USTUHealthComponent::IsHealthFull() const
{
    return FMath::IsNearlyEqual(Health, MaxHealth);
}

void USTUHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	SetHealth(MaxHealth);

    check(MaxHealth > 0);

	AActor* ComponentOwner = GetOwner();

	if (ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamageHandle);
        ComponentOwner->OnTakePointDamage.AddDynamic(this, &USTUHealthComponent::OnTakePointDamage);
        ComponentOwner->OnTakeRadialDamage.AddDynamic(this, &USTUHealthComponent::OnTakeRadialDamage);
	    
	}
}

void USTUHealthComponent::OnTakeAnyDamageHandle(
    AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    
}

void USTUHealthComponent::OnTakePointDamage(AActor* DamagedActor, float Damage, AController* InstigatedBy, FVector HitLocation,
    UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const UDamageType* DamageType, AActor* DamageCauser)
{
    // POINT
    const float FinalDamage = Damage * GetPointDamageModifier(DamagedActor, BoneName);
    UE_LOG(LogHealthComponent, Display, TEXT("%f final damage: %f, Bone %s"), Damage, FinalDamage, *BoneName.ToString());
    ApplyDamage(FinalDamage, InstigatedBy);
}

void USTUHealthComponent::OnTakeRadialDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, FVector Origin,
    FHitResult HitInfo, AController* InstigatedBy, AActor* DamageCauser)
{
    // RADIAL
    ApplyDamage(Damage, InstigatedBy);
}

void USTUHealthComponent::HealUpdate()
{
    SetHealth(Health + HealModifier);

    if (IsHealthFull() && GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
    }
}

void USTUHealthComponent::SetHealth(float NewHealth) 
{
    const float NextHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    const float HealthDelta = NextHealth - Health;

    Health = NextHealth;

    Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    OnHealthChanged.Broadcast(Health, HealthDelta);
}

void USTUHealthComponent::PlayCameraShake() 
{
    const auto Pawn = Cast<APawn>(GetOwner());
    if (Pawn && !IsDead())
    {
        auto Controller = Pawn->GetController<APlayerController>();
        if (Controller && Controller->PlayerCameraManager)
        {
            Controller->PlayerCameraManager->StartCameraShake(CameraShake);
        }
    }
}

bool USTUHealthComponent::IsFriend(const AController* OtherController) const
{
    const auto OwnerPawn = Cast<APawn>(GetOwner());
    if (OwnerPawn)
    {
        const auto OwnerController = OwnerPawn->GetController();
        if (OwnerController)
        {
            const bool AreEnemies = STUUtils::AreEnemies(OwnerController, OtherController);
            return !AreEnemies;
        }
    }
    
    return false;
}

void USTUHealthComponent::Killed(AController* KillerController)
{
    if (GetWorld())
    {
        const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            const auto OwnerPlayer = Cast<APawn>(GetOwner());
            const auto VictimController = OwnerPlayer ? OwnerPlayer->GetController() : nullptr;

            GameMode->Killed(KillerController, VictimController);
        }
    }
    

    
}

void USTUHealthComponent::ApplyDamage(float Damage, AController* InstigatedBy)
{
    if (Damage <= 0 || IsDead() || !GetWorld())
        return;

    const bool Friend = IsFriend(InstigatedBy);

    if (!IsFriendFire && Friend) return;
    
    SetHealth(Health - Damage);

    GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);

    if (IsDead())
    {
        Killed(InstigatedBy);
        OnDeath.Broadcast();
    }
    else if (AutoHeal) 
    {
        GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &USTUHealthComponent::HealUpdate, HealUpdateTime, true, HealDelay);
    }

    PlayCameraShake();

    /* if (DamageType)
    {
        if (DamageType->IsA<USTUFireDamageType>())
        {
            UE_LOG(LogHealthComponent, Display, TEXT("So Hot :("));
        }
        else if (DamageType->IsA<USTUIceDamageType>())
        {
            UE_LOG(LogHealthComponent, Display, TEXT("She is cold as ice ^^"));
        }
    }*/
}

float USTUHealthComponent::GetPointDamageModifier(AActor* DamagedActor, const FName& BoneName)
{
    const auto Character = Cast<ACharacter>(DamagedActor);

    if (Character && Character->GetMesh() && Character->GetMesh()->GetBodyInstance(BoneName))
    {
        const auto PhysMaterial = Character->GetMesh()->GetBodyInstance(BoneName)->GetSimplePhysicalMaterial();

        if (DamageModifiers.Contains(PhysMaterial))
        {
            return DamageModifiers[PhysMaterial];
        }
    }

    return 1;
}
