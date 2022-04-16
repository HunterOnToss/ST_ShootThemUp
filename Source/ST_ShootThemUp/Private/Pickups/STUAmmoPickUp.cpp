// Shoot Them Up Game. All Right Reserved 2022.


#include "Pickups/STUAmmoPickUp.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"
#include "STUUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, All, All);

bool ASTUAmmoPickUp::GivePickupTo(APawn* PlayerPawn)
{
    const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(PlayerPawn);
    
    if (HealthComponent && !HealthComponent->IsDead())
    {
        const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(PlayerPawn);

        if (WeaponComponent)
        {
            return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);
        }
    }

    return false;
}