// Shoot Them Up Game. All Right Reserved 2022.


#include "UI/STUPauseWidget.h"
#include "GameFramework/GameMode.h"
#include "Components/Button.h"

void USTUPauseWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (ClearPauseButton)
    {
        ClearPauseButton->OnClicked.AddDynamic(this, &USTUPauseWidget::OnClearPause);
    }

}

void USTUPauseWidget::OnClearPause()
{
    if (GetWorld() && GetWorld()->GetAuthGameMode())
    {
        GetWorld()->GetAuthGameMode()->ClearPause();
    }
}
