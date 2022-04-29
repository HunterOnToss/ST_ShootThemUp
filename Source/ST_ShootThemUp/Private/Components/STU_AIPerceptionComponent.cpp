// Shoot Them Up Game. All Right Reserved 2022.


#include "Components/STU_AIPerceptionComponent.h"
#include "AIController.h"
#include "STUUtils.h"
#include "STUHealthComponent.h"
#include "Perception/AISense_Damage.h"
#include "Perception/AISense_Sight.h"

AActor* USTU_AIPerceptionComponent::GetClosestEnemy() const
{
    TArray<AActor*> PerceiveActors;
    GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PerceiveActors);

    if (PerceiveActors.Num() == 0)
    {
        GetCurrentlyPerceivedActors(UAISense_Damage::StaticClass(), PerceiveActors);
        if (PerceiveActors.Num() == 0)
        {
            return nullptr;    
        }
    }

    const auto Controller = Cast<AAIController>(GetOwner());

    if (Controller)
    {
        const auto Pawn = Controller->GetPawn();
        if (Pawn)
        {
            float BestDistance = MAX_FLT;
            AActor* BestPawn = nullptr;

            for (const auto Elem : PerceiveActors)
            {
                const auto HealthComp = Elem->FindComponentByClass<USTUHealthComponent>();

                const auto PerceivePawn = Cast<APawn>(Elem);
                const auto AreEnemies = PerceivePawn && STUUtils::AreEnemies(Controller, PerceivePawn->Controller);
                
                if (HealthComp && !HealthComp->IsDead() && AreEnemies) 
                {
                    const auto CurrentDistance = (Elem->GetActorLocation() - Pawn->GetActorLocation()).Size();
                    if (CurrentDistance < BestDistance)
                    {
                        BestDistance = CurrentDistance;
                        BestPawn = Elem;
                    }
                }
            }
            return BestPawn;
        }
    }
    return nullptr;
}
