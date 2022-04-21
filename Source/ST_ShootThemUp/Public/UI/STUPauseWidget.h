// Shoot Them Up Game. All Right Reserved 2022.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUPauseWidget.generated.h"

class UButton;

UCLASS()
class ST_SHOOTTHEMUP_API USTUPauseWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    
    virtual bool Initialize() override;

protected:
    
    UPROPERTY(meta=(BindWidget))
    UButton* ClearPauseButton;

private:
    
    UFUNCTION()
    void OnClearPause();
    
};
