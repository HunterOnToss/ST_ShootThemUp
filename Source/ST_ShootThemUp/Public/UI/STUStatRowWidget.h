// Shoot Them Up Game. All Right Reserved 2022.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUStatRowWidget.generated.h"

class UImage;
class UTextBlock;


UCLASS()
class ST_SHOOTTHEMUP_API USTUStatRowWidget : public UUserWidget
{
	GENERATED_BODY()

public:

    void SetPlayerName(const FText& Text);
    void SetKills(const FText& Text);
    void SetDeaths(const FText& Text);
    void SetTeam(const FText& Text);
    void SetPlayerIndicatorVisibility(bool Visible);
    
protected:

    UPROPERTY(meta=(BindWidget))
    UTextBlock* PlayerNameTextBlock;

    UPROPERTY(meta=(BindWidget))
    UTextBlock* KillsTextBlock;

    UPROPERTY(meta=(BindWidget))
    UTextBlock* DeathsTextBlock;

    UPROPERTY(meta=(BindWidget))
    UTextBlock* TeamTextBlock;

    UPROPERTY(meta=(BindWidget))
    UImage* PlayerIndicatorImage;    
};
