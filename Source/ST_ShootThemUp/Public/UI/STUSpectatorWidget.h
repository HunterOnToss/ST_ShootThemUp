// Shoot Them Up Game. All Right Reserved 2022.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUSpectatorWidget.generated.h"


UCLASS()
class ST_SHOOTTHEMUP_API USTUSpectatorWidget : public UUserWidget
{
	GENERATED_BODY()
    
public:
    UFUNCTION(BlueprintCallable, Category="UI")
    bool GetRespawnTime(int32& RespawnTime) const;
    
};
