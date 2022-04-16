// Shoot Them Up Game. All Right Reserved 2022.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/STUBasePickUp.h"
#include "STUHealthPickUp.generated.h"

/**
 * 
 */
UCLASS()
class ST_SHOOTTHEMUP_API ASTUHealthPickUp : public ASTUBasePickUp
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "100.0"))
    float HealthAmount = 100.f;

private:

	virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
