// Shoot Them Up Game. All Right Reserved 2022.


#include "Player/STUPlayerController.h"
#include "STURespawnComponent.h"

ASTUPlayerController::ASTUPlayerController()
{
    RespawnComponent = CreateDefaultSubobject<USTURespawnComponent>("RespawnComponent");
}
