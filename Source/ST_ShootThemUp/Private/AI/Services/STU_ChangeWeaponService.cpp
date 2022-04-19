// Shoot Them Up Game. All Right Reserved 2022.


#include "AI/Services/STU_ChangeWeaponService.h"
#include "AIController.h"
#include "STUAIWeaponComponent.h"
#include "STUWeaponComponent.h"

USTU_ChangeWeaponService::USTU_ChangeWeaponService()
{
    NodeName = "Weapon Change";
}

void USTU_ChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const auto Controller = OwnerComp.GetAIOwner();

    if (Controller)
    {
        const auto WeaponComponent = Controller->GetPawn()->FindComponentByClass<USTUWeaponComponent>();
        if (WeaponComponent)
        {
            UE_LOG(LogTemp, Display, TEXT("FIND!!!!"));
            if (Probability > 0 && FMath::FRand() <= Probability)
            {
                UE_LOG(LogTemp, Display, TEXT("CHANGE!!!!"));
                WeaponComponent->NextWeapon();
            }
        }
    }
    
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
