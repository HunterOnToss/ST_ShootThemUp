// Shoot Them Up Game. All Right Reserved 2022.


#include "AI/Decorator/STU_NeedAmmoDecorator.h"
#include "AIController.h"
#include "STUWeaponComponent.h"

USTU_NeedAmmoDecorator::USTU_NeedAmmoDecorator()
{
    NodeName = "Need Ammo";
}

bool USTU_NeedAmmoDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    const auto Controller = OwnerComp.GetAIOwner();

    if (Controller)
    {
        const auto WeaponComponent = Controller->GetPawn()->FindComponentByClass<USTUWeaponComponent>();

        if (WeaponComponent)
        {
            return WeaponComponent->NeedAmmo(WeaponType);
        }
    }

    return false;
    //return Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
}
