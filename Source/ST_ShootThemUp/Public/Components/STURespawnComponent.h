// Shoot Them Up Game. All Right Reserved 2022.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STURespawnComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ST_SHOOTTHEMUP_API USTURespawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USTURespawnComponent();

    void Respawn(int32 RespawnTime);
    int32 GetRespawnCountDown() const { return RespawnCountdown; }
    bool IsRespawnInProgress() const;

private:
    FTimerHandle RespawnTimerHandle;
    int32 RespawnCountdown = 0;

    void RespawnTimerUpdate();
};
