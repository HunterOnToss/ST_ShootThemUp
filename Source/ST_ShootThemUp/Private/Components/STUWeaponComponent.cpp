// Shoot Them Up Game. All Right Reserved 2022.


#include "Components/STUWeaponComponent.h"
#include "Weapon/STUBaseWeapon.h"
#include "GameFramework/Character.h"
#include "Animation/STUEquipFinishedAnimNotify.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All);

USTUWeaponComponent::USTUWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USTUWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

    CurrentWeaponIndex = 0;
    InitAnimations();
    SpawnWeapons();
    EquipWeapon(CurrentWeaponIndex);
}

void USTUWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason) 
{
    CurrentWeapon = nullptr;
    for (auto Weapon : Weapons)
    {
        Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
        Weapon->Destroy();
    }
    Weapons.Empty();
    Super::EndPlay(EndPlayReason);
}

void USTUWeaponComponent::StartFire() 
{
    if (CanFire())
    {
        CurrentWeapon->StartFire();
    }
}

void USTUWeaponComponent::EndFire() 
{
    if (!CurrentWeapon)
        return;

    CurrentWeapon->StopFire();
}

void USTUWeaponComponent::NextWeapon() 
{
    if (CanEquip())
    {
        CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
        EquipWeapon(CurrentWeaponIndex);
    }
}

void USTUWeaponComponent::Reload() 
{
    PlayAnimMontage(CurrentReloadAnimMontage);
}

void USTUWeaponComponent::SpawnWeapons()
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character || !GetWorld())
        return;

    for (auto elem : WeaponData)
    {
        auto Weapon = GetWorld()->SpawnActor<ASTUBaseWeapon>(elem.WeaponClass);

        if (!Weapon)
        {
            continue;
        }
        Weapon->SetOwner(Character);
        Weapons.Add(Weapon);
        AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
    }
}

void USTUWeaponComponent::AttachWeaponToSocket(ASTUBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName) 
{
    if (Weapon || SceneComponent)
    {
        FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
        Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
    }
}

void USTUWeaponComponent::EquipWeapon(int32 WeaponIndex) 
{
    if (WeaponIndex < 0 || WeaponIndex >= Weapons.Num())
    {
        UE_LOG(LogWeaponComponent, Warning, TEXT("Invalid Weapon Index"));
        return;
    }
    ACharacter* Character = Cast<ACharacter>(GetOwner());

    if (Character)
    {
        if (CurrentWeapon)
        {
            CurrentWeapon->StopFire();
            AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
        }

        CurrentWeapon = Weapons[WeaponIndex];
        //CurrentReloadAnimMontage = WeaponData[WeaponIndex].ReloadAnimMontage;

        const auto CurrentWeaponData = WeaponData.FindByPredicate([&](const FWeaponData& Data){
            return Data.WeaponClass == CurrentWeapon->GetClass();
        });

        CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;

        AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
    }

    EquipAnimInProgress = true;
    PlayAnimMontage(EquipAnimMontage);
}

void USTUWeaponComponent::PlayAnimMontage(UAnimMontage* Animation) 
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (Character)
    {
        Character->PlayAnimMontage(Animation);
    }
}

void USTUWeaponComponent::InitAnimations() 
{
    if (EquipAnimMontage)
    {
        const auto NotifyEvent = EquipAnimMontage->Notifies;

        for (auto elem : NotifyEvent)
        {
           auto EquipFinishedNotify = Cast<USTUEquipFinishedAnimNotify>(elem.Notify);
           if (EquipFinishedNotify)
           {
               EquipFinishedNotify->OnNotified.AddUObject(this, &USTUWeaponComponent::OnEquipFinished);
               break;
           }
        }
    }
}

void USTUWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComponent)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (Character && MeshComponent == Character->GetMesh())
    {
        EquipAnimInProgress = false;
    }
}

bool USTUWeaponComponent::CanFire() const 
{
    return CurrentWeapon && !EquipAnimInProgress;
}

bool USTUWeaponComponent::CanEquip() const
{
    return !EquipAnimInProgress;
}
