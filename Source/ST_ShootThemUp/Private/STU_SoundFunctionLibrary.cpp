// Shoot Them Up Game. All Right Reserved 2022.


#include "STU_SoundFunctionLibrary.h"
#include "Sound/SoundClass.h"

DEFINE_LOG_CATEGORY_STATIC(LogSound, All, All);

void USTU_SoundFunctionLibrary::SetSoundClassVolume(USoundClass* SoundClass, float Volume)
{
    if (SoundClass)
    {
        SoundClass->Properties.Volume = FMath::Clamp(Volume, 0.0f, 1.0f);
        UE_LOG(LogSound, Display, TEXT("Sound class volume was chagne: %s = %f"), *SoundClass->GetName(),
            SoundClass->Properties.Volume);
    }
}

void USTU_SoundFunctionLibrary::ToggleSoundClassVolume(USoundClass* SoundClass)
{
    if (SoundClass)
    {
        const float NextVolume = SoundClass->Properties.Volume > 0.0f? 0.0f : 1.0f;

        SetSoundClassVolume(SoundClass, NextVolume);
    }
    
}
