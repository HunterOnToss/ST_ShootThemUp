// Shoot Them Up Game. All Right Reserved 2022.


#include "Menu/STUMenuPlayerController.h"
#include "STUGameInstance.h"

void ASTUMenuPlayerController::BeginPlay()
{
    SetInputMode(FInputModeUIOnly());
    bShowMouseCursor = true;
    Super::BeginPlay();
}
