// Shoot Them Up Game. All Right Reserved 2022.


#include "Player/STUPlayerController.h"
#include "STURespawnComponent.h"
#include "GameFramework/GameMode.h"

ASTUPlayerController::ASTUPlayerController()
{
    RespawnComponent = CreateDefaultSubobject<USTURespawnComponent>("RespawnComponent");
}

void ASTUPlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    OnNewPawn.Broadcast(InPawn);
}

void ASTUPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (InputComponent)
    {
        InputComponent->BindAction("PauseGame", IE_Pressed, this, &ASTUPlayerController::OnPauseGame);
    }
}

void ASTUPlayerController::OnPauseGame()
{
    if (GetWorld() && GetWorld()->GetAuthGameMode())
    {
        GetWorld()->GetAuthGameMode()->SetPause(this);
    }
}
