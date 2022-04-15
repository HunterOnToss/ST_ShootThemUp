// Shoot Them Up Game. All Right Reserved 2022.


#include "UI/STUBaseHUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"

void ASTUBaseHUD::DrawHUD() 
{
    Super::DrawHUD();

    DrawCrosshair();
}

void ASTUBaseHUD::BeginPlay() 
{
    Super::BeginPlay();

    auto PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHudWidgetKlass);
    
    if (PlayerHUDWidget)
    {
        PlayerHUDWidget->AddToViewport();
    }
}

void ASTUBaseHUD::DrawCrosshair()
{
    const TInterval<float> Center(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);
    
    const float HalfLineSize = 10.0f;
    const float LineThickness = 2.0f;
    const FLinearColor LineColor = FLinearColor::Green;

    DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, LineColor, LineThickness);
    DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, LineColor, LineThickness);
    
}
