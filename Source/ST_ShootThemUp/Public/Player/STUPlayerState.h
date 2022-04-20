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
    
private:
    int32 TeamID;
    FLinearColor TeamColor;
};
