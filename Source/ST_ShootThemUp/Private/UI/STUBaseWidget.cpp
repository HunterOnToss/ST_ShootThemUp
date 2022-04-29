// Shoot Them Up Game. All Right Reserved 2022.


#include "UI/STUBaseWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

void USTUBaseWidget::Show()
{
    PlayAnimation(ShowAnimation);
    UGameplayStatics::PlaySound2D(GetWorld(), OpenSound);
    
}
