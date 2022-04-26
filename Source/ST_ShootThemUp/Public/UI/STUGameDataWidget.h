// Shoot Them Up Game. All Right Reserved 2022.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUGameDataWidget.generated.h"

class ASTUGameModeBase;
class ASTUPlayerState;

UCLASS()
class ST_SHOOTTHEMUP_API USTUGameDataWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    
    UFUNCTION(BlueprintCallable, Category="UI")
    int32 GetCurrentRoundNum() const;

    UFUNCTION(BlueprintCallable, Category="UI")
    int32 GetTotalRoundsNum() const;

    UFUNCTION(BlueprintCallable, Category="UI")
    int32 GetRoundSecondsRemaining() const;

private:
    ASTUGameModeBase* GetSTUGameMode() const;
    ASTUPlayerState* GetSTUPlayerState() const;
};
