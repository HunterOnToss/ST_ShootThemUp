// Shoot Them Up Game. All Right Reserved 2022.

#include "Components/STUHealthComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "STUUtils.h"

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
	}
}

void USTUHealthComponent::OnTakeAnyDamageHandle(
    AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    if (Damage <= 0 || IsDead() || !GetWorld())
        return;

    const bool Friend = IsFriend(InstigatedBy);

    if (!IsFriendFire && Friend) return;
    
    SetHealth(Health - Damage);

    GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);

    if (IsDead())
    {
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
