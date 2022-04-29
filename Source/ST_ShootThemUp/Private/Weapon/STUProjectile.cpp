// Shoot Them Up Game. All Right Reserved 2022.

#include "Weapon/STUProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/Components/STUWeaponFXComponent.h"

ASTUProjectile::ASTUProjectile()
{
    PrimaryActorTick.bCanEverTick = false;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
    CollisionComponent->InitSphereRadius(5.0f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    CollisionComponent->bReturnMaterialOnMove = true;

    SetRootComponent(CollisionComponent);

    MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
    MovementComponent->InitialSpeed = 3000.0f;
    MovementComponent->ProjectileGravityScale = 0.0f;

    WeaponFXComponent = CreateDefaultSubobject<USTUWeaponFXComponent>("WeaponComponent");
}

void ASTUProjectile::BeginPlay()
{
    Super::BeginPlay();

    check(MovementComponent);
    check(CollisionComponent);
    check(WeaponFXComponent);

    MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
    CollisionComponent->OnComponentHit.AddDynamic(this, &ASTUProjectile::OnProjectileHit);
    CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);
    SetLifeSpan(LifeSeconds);
}

void ASTUProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (GetWorld())
    {
        MovementComponent->StopMovementImmediately();

        UGameplayStatics::ApplyRadialDamage(GetWorld(), //
            DamageAmount,                               //
            GetActorLocation(),                         //
            DamageRadius,                               //
            UDamageType::StaticClass(),                 //
            {GetOwner()},                               //
            this,                                       //
            GetController(),                            //
            DoFullDamage);

        //DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 24, FColor::Cyan, false, 5.0f);

        WeaponFXComponent->PlayImpactFx(Hit);
        Destroy();
    }
}

AController* ASTUProjectile::GetController() const
{
    const APawn* Pawn = Cast<APawn>(GetOwner());
    return Pawn ? Pawn->GetController() : nullptr;
}
