// Shoot Them Up Game. All Right Reserved 2022.


#include "STUGameInstance.h"
#include "STU_SoundFunctionLibrary.h"

void USTUGameInstance::ToggleVolume()
{
    USTU_SoundFunctionLibrary::ToggleSoundClassVolume(MasterSoundClass);
}
