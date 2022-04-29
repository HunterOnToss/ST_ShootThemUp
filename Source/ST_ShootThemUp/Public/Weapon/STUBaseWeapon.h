// Shoot Them Up Game. All Right Reserved 2022.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUCoreTypes.h"
#include "STUBaseWeapon.generated.h"

class USkeletalMeshComponent;
class UNiagaraSystem;
class UNiagaraComponent;
class USoundCue;

UCLASS()
class ST_SHOOTTHEMUP_API ASTUBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ASTUBaseWeapon();

    FOnClipEmptySignature OnClipEmpty;

	virtual void StartFire();
    virtual void StopFire();

    void ChangeClip();
    bool CanReload() const;

    FWeaponUIData GetUIData() const { return UIData; }
    FAmmoData GetAmmoData() const { return CurrentAmmo; }

    bool TryToAddAmmo(int32 ClipsAmount);

    bool IsAmmoEmpty() const;
    bool IsAmmoFull() const;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FAmmoData DefaultAmmo{15, 10, false};

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FWeaponUIData UIData;

    // ========================== VFX ==============================

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX");
    UNiagaraSystem* MuzzleFX;

    UNiagaraComponent* SpawnMuzzleFX();

    // =============================================================

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float TraceMaxDistance = 15000.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Sound")
    USoundCue* FireSound;
    
	virtual void BeginPlay() override;

	virtual void MakeTheShot();
    
    bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
    FVector GetMuzzleWorldLocation() const;
    virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;
    void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);

	void DecreaseAmmo();
    bool IsClipEmpty() const;
    void LogAmmo();

private:

	FAmmoData CurrentAmmo;

};
