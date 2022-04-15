// Shoot Them Up Game. All Right Reserved 2022.


#include "Pickups/STUAmmoPickUp.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, All, All);

bool ASTUAmmoPickUp::GivePickupTo(APawn* PlayerPawn)
{
    UE_LOG(LogAmmoPickup, Display, TEXT("Ammo Was Taken"));
    return true;
}