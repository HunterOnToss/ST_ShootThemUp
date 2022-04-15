// Shoot Them Up Game. All Right Reserved 2022.


#include "Pickups/STUHealthPickUp.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, All, All);

bool ASTUHealthPickUp::GivePickupTo(APawn* PlayerPawn)
{
    UE_LOG(LogHealthPickup, Display, TEXT("Health Was Taken"));
    return true;
}