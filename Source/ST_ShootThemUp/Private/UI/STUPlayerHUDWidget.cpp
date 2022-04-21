// Shoot Them Up Game. All Right Reserved 2022.


#include "UI/STUPlayerHUDWidget.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"
#include "STUUtils.h"

bool USTUPlayerHUDWidget::Initialize()
{
    if (GetOwningPlayer())
    {
        GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &USTUPlayerHUDWidget::OnNewPawn);
        OnNewPawn(GetOwningPlayerPawn());
    }

    return Super::Initialize();
}

void USTUPlayerHUDWidget::OnNewPawn(APawn* NewPawn)
{
    //const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(NewPawn);
    if (!NewPawn) return;
    const auto HealthComponent = NewPawn->FindComponentByClass<USTUHealthComponent>();
    if (HealthComponent && !HealthComponent->OnHealthChanged.IsBoundToObject(this))
    {
        HealthComponent->OnHealthChanged.AddUObject(this, &USTUPlayerHUDWidget::OnHealthChanged);
    }
}

float USTUPlayerHUDWidget::GetHealthPercent() const
{
    const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(GetOwningPlayerPawn());

    if (HealthComponent)
    {
        return HealthComponent->GetHealthWithPercent();
    }

    return 0.0f;
}

bool USTUPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
    const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(GetOwningPlayerPawn());

    if (WeaponComponent)
    {
        return WeaponComponent->GetCurrentWeaponUIData(UIData);
    }

    return false;
}

bool USTUPlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoData& OutAmmoData) const
{
    const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(GetOwningPlayerPawn());

    if (WeaponComponent)
    {
        return WeaponComponent->GetCurrentWeaponAmmoData(OutAmmoData);
    }

    return false;
}

bool USTUPlayerHUDWidget::IsPlayerAlive() const
{
    const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(GetOwningPlayerPawn());
    return HealthComponent && !HealthComponent->IsDead();
}

bool USTUPlayerHUDWidget::IsPlayerSpectating() const
{
    const auto Controller = GetOwningPlayer();
    return Controller && Controller->GetStateName() == NAME_Spectating;
}

void USTUPlayerHUDWidget::OnHealthChanged(float Health, float HealthDelta) 
{
    if (HealthDelta < 0.0f)
    {
        OnTakeDamage();
    }
}

