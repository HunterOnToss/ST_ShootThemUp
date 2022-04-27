// Shoot Them Up Game. All Right Reserved 2022.

#pragma once

#include "CoreMinimal.h"
#include "STUBaseWidget.h"
#include "STUPauseWidget.generated.h"

class UButton;

UCLASS()
class ST_SHOOTTHEMUP_API USTUPauseWidget : public USTUBaseWidget
{
	GENERATED_BODY()

protected:
    
    UPROPERTY(meta=(BindWidget))
    UButton* ClearPauseButton;

    virtual void NativeOnInitialized() override;
    
private:
    
    UFUNCTION()
    void OnClearPause();
    
};
