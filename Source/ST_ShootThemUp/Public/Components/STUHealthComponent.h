// Shoot Them Up Game. All Right Reserved 2022.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUCoreTypes.h"
#include "STUHealthComponent.generated.h"

class UCameraShakeBase;
class UPhysicalMaterial;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ST_SHOOTTHEMUP_API USTUHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	USTUHealthComponent();

	FOnDeathSignature OnDeath;
    FOnHealthChanged OnHealthChanged;

	UFUNCTION(BlueprintCallable, Category = "Health")
    bool IsDead() const { return FMath::IsNearlyZero(Health); }

	UFUNCTION(BlueprintCallable, Category = "Health")
    float GetHealthWithPercent() const { return Health / MaxHealth; }

	float GetHealth() const { return Health; }

	bool TryToAddHealth(float HealthAmount);
    bool IsHealthFull() const;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0", ClampMax = "1000"))
    float MaxHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal")
    bool AutoHeal = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
    float HealUpdateTime = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
    float HealDelay = 2.4f;

	// How many Health for autoheal;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
    float HealModifier = 5.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    TSubclassOf<UCameraShakeBase> CameraShake;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Team")
    bool IsFriendFire = true;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Health")
    TMap<UPhysicalMaterial*, float> DamageModifiers;
    
	virtual void BeginPlay() override;

private:
    float Health = 0.0f;
    FTimerHandle HealTimerHandle;

    // ==================  DAMAGE  ==================
	UFUNCTION()
	void OnTakeAnyDamageHandle(
        AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

    UFUNCTION()
    void OnTakePointDamage(AActor* DamagedActor, float Damage, class AController* InstigatedBy, FVector HitLocation, class UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const class UDamageType* DamageType, AActor* DamageCauser);

    UFUNCTION()
    void OnTakeRadialDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, FVector Origin, FHitResult HitInfo, class AController* InstigatedBy, AActor* DamageCauser);

    void ApplyDamage(float Damage, AController* InstigatedBy);

    float GetPointDamageModifier(AActor* DamagedActor, const FName& BoneName);

    void ReportDamage(float Damage, AController* InstigatedBy);
    
    // ==============================================
    
	void HealUpdate();
	void SetHealth(float NewHealth);

	void PlayCameraShake();
    bool IsFriend(const AController* OtherController) const;

    void Killed(AController* KillerController);
};
