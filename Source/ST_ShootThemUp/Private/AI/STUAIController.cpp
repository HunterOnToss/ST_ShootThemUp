// Shoot Them Up Game. All Right Reserved 2022.


#include "AI/STUAIController.h"
#include "AI/STUAICharacter.h"
#include "Components/STU_AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

ASTUAIController::ASTUAIController()
{
    STU_AIPerceptionComponent = CreateDefaultSubobject<USTU_AIPerceptionComponent>("AIPerceptionComponent");
    SetPerceptionComponent(*STU_AIPerceptionComponent);

    bWantsPlayerState = true;
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

    const auto AimActor = GetFocusOnActor();
    SetFocus(AimActor);
}

AActor* ASTUAIController::GetFocusOnActor() const
{
    if (Blackboard)
    {
        return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
    }

    return nullptr;
}
