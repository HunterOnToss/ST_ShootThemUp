// Shoot Them Up Game. All Right Reserved 2022.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "STUPlayerState.generated.h"

UCLASS()
class ST_SHOOTTHEMUP_API ASTUPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
    void SetTeamID(int32 ID){ TeamID = ID;}
    int32 GetTeamID() const { return TeamID;}

    void SetTeamColor(const FLinearColor& Color) { TeamColor = Color;}
    FLinearColor GetTeamColor() const { return TeamColor;}

    void AddKill(){KillsNum++;}
    int32 GetKillsNum() const { return KillsNum;}
    
    void AddDeath(){DeathsNum++;}
    int32 GetDeathNum() const {return  DeathsNum;}

    void LogInfo() const;
    
private:
    int32 TeamID;
    FLinearColor TeamColor;

    int32 KillsNum = 0;
    int32 DeathsNum = 0;
    
};
