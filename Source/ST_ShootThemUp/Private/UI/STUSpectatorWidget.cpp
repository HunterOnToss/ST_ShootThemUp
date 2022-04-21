// Shoot Them Up Game. All Right Reserved 2022.


#include "UI/STUSpectatorWidget.h"
#include "STURespawnComponent.h"

bool USTUSpectatorWidget::GetRespawnTime(int32& RespawnTime) const
{
    const auto RespawnComponent = GetOwningPlayer()->FindComponentByClass<USTURespawnComponent>();
    
    if (RespawnComponent && RespawnComponent->IsRespawnInProgress())
    {
        RespawnTime = RespawnComponent->GetRespawnCountDown();
        return true;
    }
    return false;
}
