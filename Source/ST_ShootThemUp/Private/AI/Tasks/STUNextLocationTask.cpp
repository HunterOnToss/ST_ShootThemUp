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
                const bool IsFound = SearchLocation(NavSys, Pawn, Blackboard);
                if (IsFound)
                {
                    return EBTNodeResult::Succeeded;
                }
            }
        }
    }
    
    return EBTNodeResult::Failed;
}

bool USTUNextLocationTask::SearchLocation(const UNavigationSystemV1* NavSys, const APawn* Pawn, UBlackboardComponent* Blackboard) const 
{
    FNavLocation NavLocation;
    FVector Location = Pawn->GetActorLocation();

    if (!SelfCenter)
    {
        const auto CenterActor = Cast<AActor>(Blackboard->GetValueAsObject(CenterActorKey.SelectedKeyName));
        if (CenterActor)
        {
            Location = CenterActor->GetActorLocation();
        }
        else
        {
            return EBTNodeResult::Failed;
        }
    }
                
    const bool IsFound = NavSys->GetRandomReachablePointInRadius(Location, Radius, NavLocation);
    if (IsFound)
    {
        Blackboard->SetValueAsVector(AimLocationKey.SelectedKeyName, NavLocation.Location);
        return true;
    }
    return false;
}

