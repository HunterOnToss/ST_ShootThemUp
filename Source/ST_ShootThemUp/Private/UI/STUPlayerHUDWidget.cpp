// Shoot Them Up Game. All Right Reserved 2022.


#include "UI/STUPlayerHUDWidget.h"
#include "Components/STUHealthComponent.h"

float USTUPlayerHUDWidget::GetHealthPercent() const
{
    const auto Player = GetOwningPlayerPawn();
    if (Player)
    {
        const auto Component = Player->GetComponentByClass(USTUHealthComponent::StaticClass());
        const auto HealthComponent = Cast<USTUHealthComponent>(Component);

        if (HealthComponent)
        {
            return HealthComponent->GetHealthWithPercent();
        }
    }
    return 0.0f;
}