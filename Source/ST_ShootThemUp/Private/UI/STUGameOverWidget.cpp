// Shoot Them Up Game. All Right Reserved 2022.


#include "STUGameOverWidget.h"
#include "STUGameModeBase.h"
#include "STUPlayerState.h"
#include "STUStatRowWidget.h"
#include "Components/VerticalBox.h"
#include "STUUtils.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void USTUGameOverWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    
    if (GetWorld())
    {
        const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnMatchStateChange.AddUObject(this, &USTUGameOverWidget::OnMatchStateChange);
        }
    }
}

void USTUGameOverWidget::OnMatchStateChange(ESTUMatchState State)
{
    if (State == ESTUMatchState::GameOver)
    {
        UpdatePlayerStat();
    }
}

void USTUGameOverWidget::UpdatePlayerStat()
{
    if (GetWorld() && PlayerStatBox)
    {
        PlayerStatBox->ClearChildren();
        
        for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
        {
            const auto Controller = It->Get();

            if (Controller)
            {
                const auto PlayerState = Controller->GetPlayerState<ASTUPlayerState>();
                if (PlayerState)
                {
                    const auto PlayerStatRowWidget = CreateWidget<USTUStatRowWidget>(GetWorld(), PlayerStatRowWidgetKlass);
                    if (!PlayerStatRowWidget) continue;

                    PlayerStatRowWidget->SetPlayerName(FText::FromString(PlayerState->GetPlayerName()));
                    PlayerStatRowWidget->SetKills(STUUtils::TextFromInt(PlayerState->GetKillsNum()));
                    PlayerStatRowWidget->SetDeaths(STUUtils::TextFromInt(PlayerState->GetDeathNum()));
                    PlayerStatRowWidget->SetTeam(STUUtils::TextFromInt(PlayerState->GetTeamID()));
                    PlayerStatRowWidget->SetPlayerIndicatorVisibility(Controller->IsPlayerController());

                    PlayerStatBox->AddChild(PlayerStatRowWidget);
                }
            }
        }
    }
}

void USTUGameOverWidget::OnResetLevel()
{
    
}
