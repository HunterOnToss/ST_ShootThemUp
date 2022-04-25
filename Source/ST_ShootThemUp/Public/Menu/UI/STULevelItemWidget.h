// Shoot Them Up Game. All Right Reserved 2022.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUCoreTypes.h"
#include "STULevelItemWidget.generated.h"

class UButton;
class UTextBlock;
class UImage;


UCLASS()
class ST_SHOOTTHEMUP_API USTULevelItemWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

    UPROPERTY(meta=(BindWidget))
    UButton* LevelSelectButton;

    UPROPERTY(meta=(BindWidget))
    UTextBlock* LevelNameTextBlock;

    UPROPERTY(meta=(BindWidget))
    UImage* LevelImage = nullptr;

    UPROPERTY(meta=(BindWidget))
    UImage* FrameImage = nullptr;

    virtual void NativeOnInitialized() override;
};
