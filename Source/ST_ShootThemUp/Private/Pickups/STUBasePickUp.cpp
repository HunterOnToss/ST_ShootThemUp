// Shoot Them Up Game. All Right Reserved 2022.


#include "Pickups/STUBasePickUp.h"
#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePickup, All, All);

ASTUBasePickUp::ASTUBasePickUp()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
    CollisionComponent->InitSphereRadius(50.0f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    SetRootComponent(CollisionComponent);
}

void ASTUBasePickUp::BeginPlay()
{
	Super::BeginPlay();
	
	check(CollisionComponent);
}

void ASTUBasePickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASTUBasePickUp::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    const auto Pawn = Cast<APawn>(OtherActor);

    if (GivePickupTo(Pawn))
    {
        PickupWasTaken();
    }    
}

bool ASTUBasePickUp::GivePickupTo(APawn* PlayerPawn)
{
    return false;
}

void ASTUBasePickUp::Respawn() 
{
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    GetRootComponent()->SetVisibility(true, true);
}

void ASTUBasePickUp::PickupWasTaken() 
{
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    GetRootComponent()->SetVisibility(false, true);

    FTimerHandle RespawnTimerHandle;
    GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ASTUBasePickUp::Respawn, RespawnTime);
    
}

