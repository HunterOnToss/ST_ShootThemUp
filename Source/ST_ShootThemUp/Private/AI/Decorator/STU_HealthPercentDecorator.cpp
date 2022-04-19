// Shoot Them Up Game. All Right Reserved 2022.


#include "AI/Decorator/STU_HealthPercentDecorator.h"
#include "AIController.h"
#include "STUHealthComponent.h"

USTU_HealthPercentDecorator::USTU_HealthPercentDecorator()
{
    NodeName = "Health Percent";
}

bool USTU_HealthPercentDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    const auto Controller = OwnerComp.GetAIOwner();
    if (Controller)
    {
        const auto HealthComponent = Controller->GetPawn()->FindComponentByClass<USTUHealthComponent>();

        if (HealthComponent && !HealthComponent->IsDead())
        {
            return HealthComponent->GetHealthWithPercent() <= HealthPercent;                   
        }
    }

    return false;
}
