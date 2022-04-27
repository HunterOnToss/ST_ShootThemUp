// Shoot Them Up Game. All Right Reserved 2022.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUHealathBarWidget.generated.h"

class UProgressBar;

UCLASS()
class ST_SHOOTTHEMUP_API USTUHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:

    void SetHealthPercent(float Percent);
    
protected:

    UPROPERTY(meta=(BindWidget))
    UProgressBar* HealthProgressBar;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
    float PercentVisibilityThreshold = 0.8f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
    float PercentColorThreshold = 0.25f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
    FLinearColor GoodColour = FLinearColor::White;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
    FLinearColor BadColour = FLinearColor::Red;
    
};
