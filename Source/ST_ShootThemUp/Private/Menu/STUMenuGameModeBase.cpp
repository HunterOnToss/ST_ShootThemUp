// Shoot Them Up Game. All Right Reserved 2022.


#include "Menu/STUMenuGameModeBase.h"
#include "STUMenuPlayerController.h"
#include "STUMenuHUD.h"

ASTUMenuGameModeBase::ASTUMenuGameModeBase()
{
    PlayerControllerClass = ASTUMenuPlayerController::StaticClass();
    HUDClass = ASTUMenuHUD::StaticClass();
}
