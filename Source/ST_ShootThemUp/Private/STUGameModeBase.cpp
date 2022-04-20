// Shoot Them Up Game. All Right Reserved 2022.

#include "STUGameModeBase.h"
#include "AIController.h"
#include "Player/STUBaseCharacter.h"
#include "Player/STUPlayerController.h"
#include "UI/STUBaseHUD.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUGameModeBase, All, All)

ASTUGameModeBase::ASTUGameModeBase() 
{
    DefaultPawnClass = ASTUBaseCharacter::StaticClass();
    PlayerControllerClass = ASTUPlayerController::StaticClass();
    HUDClass = ASTUBaseHUD::StaticClass();
}

void ASTUGameModeBase::StartPlay()
{
    Super::StartPlay();

    SpawnBots();

    CurrentRound = 1;
    StartRound();
}

UClass* ASTUGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
    if (InController && InController->IsA<AAIController>())
    {
        return AIPawnClass;
    }
    
    return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void ASTUGameModeBase::SpawnBots() 
{
    if (GetWorld())
    {
        for(int32 i = 0; i < GameData.PlayerNum - 1; i++)
        {
            FActorSpawnParameters SpawnInfo;
            SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

            const auto STUAIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
            RestartPlayer(STUAIController);
        }
    }
}

void ASTUGameModeBase::StartRound()
{
    RoundCountDown = GameData.RoundTime;
    GetWorldTimerManager().SetTimer(GameRoundTimerHandle, this, &ASTUGameModeBase::GameTimerUpdate, 1.0f, true);
}

void ASTUGameModeBase::GameTimerUpdate()
{
    UE_LOG(LogSTUGameModeBase, Display, TEXT("Time: %i / Round: %i/%i"), RoundCountDown, CurrentRound, GameData.RoundNums);
    
    if (--RoundCountDown == 0)
    {
        UE_LOG(LogSTUGameModeBase, Display, TEXT("RCD: %i"), RoundCountDown);
        
        GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);

        if (CurrentRound + 1 <= GameData.RoundNums)
        {
            ++CurrentRound;
            ResetPlayers();
            StartRound();
        }
        else
        {
            UE_LOG(LogSTUGameModeBase, Display, TEXT("======= GAME OVER ======="));
        }
    }
}

void ASTUGameModeBase::ResetPlayers()
{
    if (GetWorld())
    {
        for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
        {
            ResetOnePlayer(It->Get());
        }
    }
}

void ASTUGameModeBase::ResetOnePlayer(AController* Controller)
{
    if (Controller && Controller->GetPawn())
    {
        Controller->GetPawn()->Reset();
    }
    
    RestartPlayer(Controller);
}
