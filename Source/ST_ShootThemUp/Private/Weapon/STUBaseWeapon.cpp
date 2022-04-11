// Shoot Them Up Game. All Right Reserved 2022.


#include "Weapon/STUBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Character.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponBase, All, All);

ASTUBaseWeapon::ASTUBaseWeapon()
{

	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMesh);

}

void ASTUBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	check(WeaponMesh)
}

void ASTUBaseWeapon::Fire()
{
    UE_LOG(LogWeaponBase, Display, TEXT("Fire!"));

	MakeTheShot();
}

void ASTUBaseWeapon::MakeTheShot() 
{
	// ============================= Check ==============================
    if (!GetWorld())
        return;

	const ACharacter* Player = Cast<ACharacter>(GetOwner());
    if (!Player)
        return;

	const APlayerController* Controller = Player->GetController<APlayerController>();
    if (!Controller)
        return;

	// ============================= Calculate Trace  ==============================
	FVector ViewLocation;
    FRotator ViewRotation;
	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);

	const FTransform SocketTransform = WeaponMesh->GetSocketTransform(MuzzleSocketName);

	const FVector TraceStart = ViewLocation; // SocketTransform.GetLocation();
    const FVector ShootDirection = ViewRotation.Vector(); // SocketTransform.GetRotation().GetForwardVector();
    const FVector TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;

	// ============================= Make Shoot ====================================

	FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(Player);

	FHitResult HitResult;
    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);

	if (HitResult.bBlockingHit)
    {
        DrawDebugLine(GetWorld(), SocketTransform.GetLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);
        DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Magenta, false, 5.0f);

		UE_LOG(LogWeaponBase, Display, TEXT("====== Bone: %s ======"), *HitResult.BoneName.ToString());
	} 
	else 
	{
        DrawDebugLine(GetWorld(), SocketTransform.GetLocation(), TraceEnd, FColor::Red, false, 3.0f, 0, 3.0f);
	}
}
