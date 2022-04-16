// Shoot Them Up Game. All Right Reserved 2022.


#include "Pickups/STUHealthPickUp.h"
#include "Components/STUHealthComponent.h"
#include "STUUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, All, All);

bool ASTUHealthPickUp::GivePickupTo(APawn* PlayerPawn)
{
    
    const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(PlayerPawn);
    if (HealthComponent)
    {
        return HealthComponent->TryToAddHealth(HealthAmount);
    }

    return false;
}