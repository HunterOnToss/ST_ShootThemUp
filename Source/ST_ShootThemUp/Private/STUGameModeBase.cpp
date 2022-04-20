// Shoot Them Up Game. All Right Reserved 2022.

#include "STUGameModeBase.h"
#include "AIController.h"
#include "Player/STUBaseCharacter.h"
#include "Player/STUPlayerController.h"
#include "UI/STUBaseHUD.h"
#include "STUPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUGameModeBase, All, All)

ASTUGameModeBase::ASTUGameModeBase() 
{
    DefaultPawnClass = ASTUBaseCharacter::StaticClass();
    PlayerControllerClass = ASTUPlayerController::StaticClass();
    HUDClass = ASTUBaseHUD::StaticClass();
    PlayerStateClass = ASTUPlayerState::StaticClass();
}

void ASTUGameModeBase::StartPlay()
{
    Super::StartPlay();

    SpawnBots();
    CreateTeamsInfo();
    
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
    SetPlayerColour(Controller);
}

void ASTUGameModeBase::CreateTeamsInfo()
{
    if (GetWorld())
    {
        int32 TeamID = 1;
        for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
        {
            const auto Controller = It->Get();
            if(!Controller) continue;

            const auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
            if(!PlayerState) continue;

            PlayerState->SetTeamID(TeamID);
            PlayerState->SetTeamColor(DetermineColorByTeamID(TeamID));
            SetPlayerColour(Controller);
            
            TeamID = TeamID == 1 ? 2 : 1;
        }
    }
}

FLinearColor ASTUGameModeBase::DetermineColorByTeamID(int32 TeamID) const
{
    if (TeamID - 1 < GameData.TeamColors.Num())
    {
        return GameData.TeamColors[TeamID - 1];
    }

    const auto DefaultColor = *GameData.DefaultTeamColor.ToString();
    UE_LOG(LogSTUGameModeBase, Warning, TEXT("No Color for Team ID: %i, set to Default: %s"), TeamID, DefaultColor);
    return GameData.DefaultTeamColor;
}

void ASTUGameModeBase::SetPlayerColour(AController* Controller)
{
    if (Controller)
    {
        const auto Character = Cast<ASTUBaseCharacter>(Controller->GetPawn());
        if (Character)
        {
            const auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);

            Character->SetPlayerColor(PlayerState->GetTeamColor());

        }
    }
}
