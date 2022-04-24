// Shoot Them Up Game. All Right Reserved 2022.


#include "Menu/UI/STUMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "STUGameInstance.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUMenuWidget, All, All)

void USTUMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (StartGameButton)
    {
        StartGameButton->OnClicked.AddDynamic(this, &USTUMenuWidget::OnStartGame);
    }

    if (QuitGameButton)
    {
        QuitGameButton->OnClicked.AddDynamic(this, &USTUMenuWidget::OnQuitGame);
    }
}

void USTUMenuWidget::OnStartGame()
{

    if (GetWorld())
    {
        const auto STUGameInstance = GetWorld()->GetGameInstance<USTUGameInstance>();

        if (STUGameInstance)
        {
            if (STUGameInstance->GetStartupLevelName().IsNone())
            {
                UE_LOG(LogSTUMenuWidget, Error, TEXT("Level Not Found!"));
                return;
            }
            else
            {
                UGameplayStatics::OpenLevel(this, STUGameInstance->GetStartupLevelName());    
            }
        }
        
    }
}

void USTUMenuWidget::OnQuitGame()
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}
