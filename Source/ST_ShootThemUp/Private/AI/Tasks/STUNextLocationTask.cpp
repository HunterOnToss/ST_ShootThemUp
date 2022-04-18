// Shoot Them Up Game. All Right Reserved 2022.


#include "AI/Tasks/STUNextLocationTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"

USTUNextLocationTask::USTUNextLocationTask() 
{
    NodeName = "Next Location";

}

EBTNodeResult::Type USTUNextLocationTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    const auto Controller = OwnerComp.GetAIOwner();
    const auto Blackboard = OwnerComp.GetBlackboardComponent();

    if (Controller && Blackboard)
    {
        const auto Pawn = Controller->GetPawn();

        if (Pawn)
        {
            const auto NavSys = UNavigationSystemV1::GetCurrent(Pawn);
            if (NavSys)
            {
                FNavLocation NavLoction;
                const bool IsFound = NavSys->GetRandomReachablePointInRadius(Pawn->GetActorLocation(), Radius, NavLoction);
                if (IsFound)
                {
                    Blackboard->SetValueAsVector(AimLocationKey.SelectedKeyName, NavLoction.Location);
                    return EBTNodeResult::Succeeded;
                }
            }
        }
    }
    
    return EBTNodeResult::Failed;
}
