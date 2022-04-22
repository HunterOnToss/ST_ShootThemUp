// Shoot Them Up Game. All Right Reserved 2022.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUCoreTypes.h"
#include "STUGameOverWidget.generated.h"

class UVerticalBox;
class UButton;

UCLASS()
class ST_SHOOTTHEMUP_API USTUGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

    UPROPERTY(meta=(BindWidget))
    UVerticalBox* PlayerStatBox;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
    TSubclassOf<UUserWidget> PlayerStatRowWidgetKlass;

    UPROPERTY(meta=(BindWidget))
    UButton* ResetLevelButton;

    virtual void NativeOnInitialized() override;

private:

    void OnMatchStateChange(ESTUMatchState State);
    void UpdatePlayerStat();

    UFUNCTION()
    void OnResetLevel();
};
