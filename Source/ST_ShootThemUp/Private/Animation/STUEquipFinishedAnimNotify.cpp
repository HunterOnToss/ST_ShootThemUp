// Shoot Them Up Game. All Right Reserved 2022.


#include "Animation/STUEquipFinishedAnimNotify.h"

void USTUEquipFinishedAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) 
{
    OnNotified.Broadcast(MeshComp);
    Super::Notify(MeshComp, Animation);
}