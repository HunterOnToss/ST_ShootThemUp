// Shoot Them Up Game. All Right Reserved 2022.


#include "Player/STUPlayerController.h"
#include "STURespawnComponent.h"

ASTUPlayerController::ASTUPlayerController()
{
    RespawnComponent = CreateDefaultSubobject<USTURespawnComponent>("RespawnComponent");
}

void ASTUPlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    OnNewPawn.Broadcast(InPawn);
}
