// Shoot Them Up Game. All Right Reserved 2022.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "STUCoreTypes.h"
#include "STUGameModeBase.generated.h"

class AAIController;

UCLASS()
class ST_SHOOTTHEMUP_API ASTUGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASTUGameModeBase();

    FOnMatchStateChangeSignature OnMatchStateChange;

    virtual void StartPlay() override;
    virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

    void Killed(AController* KillerController, AController* VictimController);

    UFUNCTION(BlueprintCallable, Category="UI")
    FGameData GetGameData() const { return GameData;}
    
    UFUNCTION(BlueprintCallable, Category="UI")
    int32 GetCurrentRoundNum() const {return CurrentRound;}
    
    UFUNCTION(BlueprintCallable, Category="UI")
    int32 GetRoundSecondRemaining() const {return RoundCountDown;}

    void RespawnRequest(AController* Controller);

    virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate) override;
    virtual bool ClearPause() override;
    
protected:
    UPROPERTY(EditDefaultsOnly, Category="Game")
    TSubclassOf<AAIController>AIControllerClass;

    UPROPERTY(EditDefaultsOnly, Category="Game")
    TSubclassOf<APawn> AIPawnClass;
    
    UPROPERTY(EditDefaultsOnly, Category="Game")
    FGameData GameData;

private:

    ESTUMatchState MatchState = ESTUMatchState::WaitingToStart;

    int32 CurrentRound = 1;
    int32 RoundCountDown = 0;
    FTimerHandle GameRoundTimerHandle;

    void SpawnBots();
    void StartRound();
    void GameTimerUpdate();

    void ResetPlayers();
    void ResetOnePlayer(AController* Controller);

    void CreateTeamsInfo();
    FLinearColor DetermineColorByTeamID(int32 TeamID) const;
    void SetPlayerColour(AController* Controller);
    void LogPlayerInfo();

    void StartRespawn(AController* Controller);

    void GameOver();
    void SetMatchState(ESTUMatchState State);

    void StopAllFire();
};
