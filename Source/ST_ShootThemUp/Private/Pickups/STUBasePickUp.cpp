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

    GenerateRotationYaw();
}

void ASTUBasePickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    AddActorLocalRotation(FRotator(0.0f, RotationYaw, 0.0f));

}

bool ASTUBasePickUp::CouldBeTaken() const
{
    return !GetWorldTimerManager().IsTimerActive(RespawnTimerHandle);
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
    GenerateRotationYaw();
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    GetRootComponent()->SetVisibility(true, true);
}

void ASTUBasePickUp::GenerateRotationYaw() 
{
    const auto Direction = FMath::RandBool() ? 1.0f : -1.0f;
    RotationYaw = FMath::RandRange(1.0f, 2.0f) * Direction;
}

void ASTUBasePickUp::PickupWasTaken() 
{
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    GetRootComponent()->SetVisibility(false, true);
    
    GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ASTUBasePickUp::Respawn, RespawnTime);
    
}

