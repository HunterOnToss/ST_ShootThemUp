// Shoot Them Up Game. All Right Reserved 2022.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "STU_NeedAmmoDecorator.generated.h"

class ASTUBaseWeapon;

UCLASS()
class ST_SHOOTTHEMUP_API USTU_NeedAmmoDecorator : public UBTDecorator
{
	GENERATED_BODY()

public:
    USTU_NeedAmmoDecorator();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
    TSubclassOf<ASTUBaseWeapon> WeaponType;
    
protected:

    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
