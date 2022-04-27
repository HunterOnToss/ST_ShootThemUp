// Shoot Them Up Game. All Right Reserved 2022.


#include "Menu/UI/STUMenuWidget.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "STULevelItemWidget.h"
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

    InitLevelItems();
}

void USTUMenuWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
    if (Animation == HideAnimation)
    {
        if (GetWorld())
        {
            const auto STUGameInstance = GetGameInstance();

            if (STUGameInstance)
            {
                UGameplayStatics::OpenLevel(this, STUGameInstance->GetStartupLevel().LevelName);
            }
        }
    }
}

void USTUMenuWidget::OnStartGame()
{
    PlayAnimation(HideAnimation);
}
void USTUMenuWidget::InitLevelItems()
{
    const auto STUGameInstance = GetGameInstance();

    if (STUGameInstance)
    {
        checkf(STUGameInstance->GetLevelsData().Num() != 0, TEXT("Level Data is must not be empty!"));
        if (LevelItemBox)
        {
            LevelItemBox->ClearChildren();

            for (auto OneLevelData : STUGameInstance->GetLevelsData())
            {
                const auto LevelItemWidget = CreateWidget<USTULevelItemWidget>(GetWorld(), LevelItemWidgetKlass);
                if (!LevelItemWidget) continue;

                LevelItemWidget->SetLevelData(OneLevelData);
                LevelItemWidget->OnLevelSelected.AddUObject(this, &USTUMenuWidget::OnLevelSelected);

                LevelItemBox->AddChild(LevelItemWidget);
                LevelItemWidgets.Add(LevelItemWidget);
            }

            if (STUGameInstance->GetStartupLevel().LevelName.IsNone())
            {
                OnLevelSelected(STUGameInstance->GetLevelsData()[0]);
            }
            else
            {
                OnLevelSelected(STUGameInstance->GetStartupLevel());
            }
        }
    }
}

void USTUMenuWidget::OnQuitGame()
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

void USTUMenuWidget::OnLevelSelected(const FLevelData& Data)
{
    const auto STUGameInstance = GetGameInstance();

    if (STUGameInstance)
    {
        STUGameInstance->SetStartupLevel(Data);

        for (auto OneLevelItemWidget : LevelItemWidgets)
        {
            if (OneLevelItemWidget)
            {
                const auto IsSelected = Data.LevelName == OneLevelItemWidget->GetLevelData().LevelName;
                OneLevelItemWidget->SetSelected(IsSelected);
            }
        }
    }
}

USTUGameInstance* USTUMenuWidget::GetGameInstance() const
{
    if (GetWorld())
    {
        return GetWorld()->GetGameInstance<USTUGameInstance>();
    }

    return nullptr;
}
