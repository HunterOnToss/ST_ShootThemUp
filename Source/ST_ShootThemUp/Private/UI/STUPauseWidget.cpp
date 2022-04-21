// Shoot Them Up Game. All Right Reserved 2022.


#include "UI/STUPauseWidget.h"
#include "GameFramework/GameMode.h"
#include "Components/Button.h"

bool USTUPauseWidget::Initialize()
{
    const auto InitStatus =  Super::Initialize();

    if (ClearPauseButton)
    {
        ClearPauseButton->OnClicked.AddDynamic(this, &USTUPauseWidget::OnClearPause);
    }

    return InitStatus;
}

void USTUPauseWidget::OnClearPause()
{
    if (GetWorld() && GetWorld()->GetAuthGameMode())
    {
        GetWorld()->GetAuthGameMode()->ClearPause();
    }
}
