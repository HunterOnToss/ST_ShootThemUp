// Shoot Them Up Game. All Right Reserved 2022.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBasePickUp.generated.h"

class USphereComponent;

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
    float RespawnTime = 5.f;

	virtual void BeginPlay() override;
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:	
	
	virtual void Tick(float DeltaTime) override;

private:

	virtual bool GivePickupTo(APawn* PlayerPawn);
	void PickupWasTaken();
    void Respawn();
};
