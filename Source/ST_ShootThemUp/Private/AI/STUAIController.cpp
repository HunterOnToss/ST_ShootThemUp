// Shoot Them Up Game. All Right Reserved 2022.


#include "AI/STUAIController.h"
#include "AI/STUAICharacter.h"


void ASTUAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    const ASTUAICharacter* STUCharacter = Cast<ASTUAICharacter>(InPawn);

    if (STUCharacter)
    {
        RunBehaviorTree(STUCharacter->BehaviorTreeAsset);
    }
}
