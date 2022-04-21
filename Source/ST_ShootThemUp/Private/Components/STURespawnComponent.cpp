// Shoot Them Up Game. All Right Reserved 2022.


#include "Components/STURespawnComponent.h"
#include "STUGameModeBase.h"

USTURespawnComponent::USTURespawnComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
    
}

void USTURespawnComponent::Respawn(int32 RespawnTime)
{
    if (GetWorld())
    {
        RespawnCountdown = RespawnTime;
        GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &USTURespawnComponent::RespawnTimerUpdate, 1.0f, true);
    }
        
}

bool USTURespawnComponent::IsRespawnInProgress() const
{
    return GetWorld() && GetWorld()->GetTimerManager().IsTimerActive(RespawnTimerHandle);
} 

void USTURespawnComponent::RespawnTimerUpdate()
{
    if (--RespawnCountdown == 0)
    {
        if (GetWorld())
        {
            const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
            if (GameMode)
            {
                GameMode->RespawnRequest(Cast<AController>(GetOwner()));
            }
        }
    }
}




