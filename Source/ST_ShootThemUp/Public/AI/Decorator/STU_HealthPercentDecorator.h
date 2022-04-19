// Shoot Them Up Game. All Right Reserved 2022.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "STU_HealthPercentDecorator.generated.h"

UCLASS()
class ST_SHOOTTHEMUP_API USTU_HealthPercentDecorator : public UBTDecorator
{
	GENERATED_BODY()

public:
    USTU_HealthPercentDecorator();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
    float HealthPercent = 0.5f;
    
    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
    
};
