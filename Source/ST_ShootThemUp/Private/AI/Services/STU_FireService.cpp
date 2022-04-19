// Shoot Them Up Game. All Right Reserved 2022.


#include "AI/Services/STU_FireService.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "STUWeaponComponent.h"

USTU_FireService::USTU_FireService()
{
    NodeName = "Fire";
}

void USTU_FireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const auto Controller = OwnerComp.GetAIOwner();
    const auto Blackboard = OwnerComp.GetBlackboardComponent();

    const auto HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);

    if (Controller)
    {
        const auto WeaponComponent = Controller->GetPawn()->FindComponentByClass<USTUWeaponComponent>();

        if (WeaponComponent)
        {
            HasAim ? WeaponComponent->StartFire() : WeaponComponent->EndFire();
        }
    }
    
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
