// Shoot Them Up Game. All Right Reserved 2022.


#include "UI/STUHealathBarWidget.h"
#include "Components/ProgressBar.h"

void USTUHealthBarWidget::SetHealthPercent(float Percent)
{
    if (HealthProgressBar)
    {
        const auto HealthBarVisibility = (Percent > PercentVisibilityThreshold || FMath::IsNearlyZero(Percent))
                                        ? ESlateVisibility::Hidden
                                        : ESlateVisibility::Visible;

        HealthProgressBar->SetVisibility(HealthBarVisibility);

        const auto HealthBarColor = Percent > PercentColorThreshold ? GoodColour : BadColour;

        HealthProgressBar->SetFillColorAndOpacity(HealthBarColor);

        HealthProgressBar->SetPercent(Percent);        
    }
}
