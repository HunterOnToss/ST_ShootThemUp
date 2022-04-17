// Shoot Them Up Game. All Right Reserved 2022.


#include "Weapon/Components/STUWeaponFXComponent.h"
//#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"



USTUWeaponFXComponent::USTUWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USTUWeaponFXComponent::PlayImpactFx(const FHitResult& Hit) 
{
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Effect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
}
