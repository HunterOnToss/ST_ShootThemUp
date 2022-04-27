// Shoot Them Up Game. All Right Reserved 2022.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUBaseWidget.generated.h"


UCLASS()
class ST_SHOOTTHEMUP_API USTUBaseWidget : public UUserWidget
{
	GENERATED_BODY()

public:

    void Show();
    
protected:

    UPROPERTY(meta=(BindWidgetAnim), Transient)
    UWidgetAnimation* ShowAnimation;
    
};
