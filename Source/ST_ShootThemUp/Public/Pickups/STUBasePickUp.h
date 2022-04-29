// Shoot Them Up Game. All Right Reserved 2022.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBasePickUp.generated.h"

class USphereComponent;
class USoundCue;

UCLASS()
class ST_SHOOTTHEMUP_API ASTUBasePickUp : public AActor
{
	GENERATED_BODY()
	
public:	

	ASTUBasePickUp();

protected:
	
	UPROPERTY(VisibleAnywhere, Category = "Pickup")
    USphereComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
    float RespawnTime = 5.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Sound")
    USoundCue* PickupTakenSound;
    
	virtual void BeginPlay() override;
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:	
	
	virtual void Tick(float DeltaTime) override;

    bool CouldBeTaken() const;

private:

	float RotationYaw = 0.0f;
    FTimerHandle RespawnTimerHandle;
    
	virtual bool GivePickupTo(APawn* PlayerPawn);
	void PickupWasTaken();
    void Respawn();
    void GenerateRotationYaw();
};
