// Shoot Them Up Game. All Right Reserved 2022.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUEnterMenuWidget.generated.h"

class UButton;

UCLASS()
class ST_SHOOTTHEMUP_API USTUEnterMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

    UPROPERTY(meta=(BindWidget))
    UButton* EnterMenuButton;

    virtual void NativeOnInitialized() override;

private:

    UFUNCTION()
    void OnGoToMenu();
    
};
