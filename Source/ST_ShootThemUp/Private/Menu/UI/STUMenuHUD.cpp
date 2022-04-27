// Shoot Them Up Game. All Right Reserved 2022.


#include "Menu/UI/STUMenuHUD.h"
#include "STUBaseWidget.h"

void ASTUMenuHUD::BeginPlay()
{
    Super::BeginPlay();

    const auto MenuWidget = CreateWidget<USTUBaseWidget>(GetWorld(), MenuWidgetKlass);

    if (MenuWidget)
    {
        MenuWidget->AddToViewport();
        MenuWidget->Show();
    }
    
}
