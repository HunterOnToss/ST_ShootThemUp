// Shoot Them Up Game. All Right Reserved 2022.


#include "UI/STUStatRowWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"


void USTUStatRowWidget::SetPlayerName(const FText& Text)
{
    if (PlayerNameTextBlock)
    {
        PlayerNameTextBlock->SetText(Text);
    }
}

void USTUStatRowWidget::SetKills(const FText& Text)
{
    if (KillsTextBlock)
    {
        KillsTextBlock->SetText(Text);
    }
}

void USTUStatRowWidget::SetDeaths(const FText& Text)
{
    if (DeathsTextBlock)
    {
        DeathsTextBlock->SetText(Text);
    }
}

void USTUStatRowWidget::SetTeam(const FText& Text)
{
    if (TeamTextBlock)
    {
        TeamTextBlock->SetText(Text);
    }
}

void USTUStatRowWidget::SetPlayerIndicatorVisibility(bool Visible)
{
    if (PlayerIndicatorImage)
    {
        PlayerIndicatorImage->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
    }
}

void USTUStatRowWidget::SetTeamColor(const FLinearColor& Colour)
{
    if (TeamImage)
    {
        TeamImage->SetColorAndOpacity(Colour);
    }
}
