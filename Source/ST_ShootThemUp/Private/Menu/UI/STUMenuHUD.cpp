// Shoot Them Up Game. All Right Reserved 2022.


#include "Menu/UI/STUMenuHUD.h"
#include "Blueprint/UserWidget.h"

void ASTUMenuHUD::BeginPlay()
{
    Super::BeginPlay();

    const auto MenuWidget = CreateWidget<UUserWidget>(GetWorld(), MenuWidgetKlass);

    if (MenuWidget)
    {
        MenuWidget->AddToViewport();
    }
    
}
