// Shoot Them Up Game. All Right Reserved 2022.


#include "UI/STUEnterMenuWidget.h"
#include "Components/Button.h"
#include "STUGameInstance.h"
#include "Kismet/GameplayStatics.h"

void USTUEnterMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (EnterMenuButton)
    {
        EnterMenuButton->OnClicked.AddDynamic(this, &USTUEnterMenuWidget::OnGoToMenu);
    }
}

void USTUEnterMenuWidget::OnGoToMenu()
{
    if (GetWorld())
    {
        const auto GameInstance = GetWorld()->GetGameInstance<USTUGameInstance>();

        if (GameInstance)
        {
            if (GameInstance->GetMenuLevelName().IsNone())
            {
                UE_LOG(LogTemp, Error, TEXT("Menu level not found"))   
            }
            else
            {
                UGameplayStatics::OpenLevel(this, GameInstance->GetMenuLevelName());
            }
        }
    }
}
