// Shoot Them Up Game. All Right Reserved 2022.


#include "AI/STUAIController.h"
#include "AI/STUAICharacter.h"
#include "Components/STU_AIPerceptionComponent.h"

ASTUAIController::ASTUAIController()
{
    STU_AIPerceptionComponent = CreateDefaultSubobject<USTU_AIPerceptionComponent>("AIPerceptionComponent");
    SetPerceptionComponent(*STU_AIPerceptionComponent);
}

void ASTUAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    const ASTUAICharacter* STUCharacter = Cast<ASTUAICharacter>(InPawn);

    if (STUCharacter)
    {
        RunBehaviorTree(STUCharacter->BehaviorTreeAsset);
    }
}

void ASTUAIController::Tick(float DeltaSeconds)
{
    
    Super::Tick(DeltaSeconds);

    const auto AimActor = STU_AIPerceptionComponent->GetClosestEnemy();
    SetFocus(AimActor);
}
