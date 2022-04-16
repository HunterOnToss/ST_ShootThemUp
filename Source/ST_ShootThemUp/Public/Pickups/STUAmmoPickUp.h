// Shoot Them Up Game. All Right Reserved 2022.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/STUBasePickUp.h"
#include "STUAmmoPickUp.generated.h"

class ASTUBaseWeapon;

UCLASS()
class ST_SHOOTTHEMUP_API ASTUAmmoPickUp : public ASTUBasePickUp
{
	GENERATED_BODY()
	
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "10.0"))
    int32 ClipsAmount = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
    TSubclassOf<ASTUBaseWeapon> WeaponType;

private:

	virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
