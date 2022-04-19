// Shoot Them Up Game. All Right Reserved 2022.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "STU_FindEnemyService.generated.h"

UCLASS()
class ST_SHOOTTHEMUP_API USTU_FindEnemyService : public UBTService
{
	GENERATED_BODY()

public:

    USTU_FindEnemyService();

protected:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
    FBlackboardKeySelector EnemyActorKey;

    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
    
};
