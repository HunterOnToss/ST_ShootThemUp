// Shoot Them Up Game. All Right Reserved 2022.


#include "Pickups/STUBasePickUp.h"

// Sets default values
ASTUBasePickUp::ASTUBasePickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASTUBasePickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASTUBasePickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

