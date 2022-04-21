// Shoot Them Up Game. All Right Reserved 2022.


#include "UI/STUBaseHUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"
#include "STUGameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUGameHUD, All, All);

void ASTUBaseHUD::DrawHUD() 
{
    Super::DrawHUD();

    //DrawCrossHair();
}

void ASTUBaseHUD::BeginPlay() 
{
    Super::BeginPlay();

    const auto PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHudWidgetKlass);
    
    if (PlayerHUDWidget)
    {
        PlayerHUDWidget->AddToViewport();
    }
}

void ASTUBaseHUD::DrawCrossHair()
{
    const TInterval<float> Center(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);
    
    constexpr float HalfLineSize = 10.0f;
    constexpr float LineThickness = 2.0f;
    const FLinearColor LineColor = FLinearColor::Green;

    DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, LineColor, LineThickness);
    DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, LineColor, LineThickness);
    
}

void ASTUBaseHUD::OnMatchStateChange(ESTUMatchState State)
{
    
}
