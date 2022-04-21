// Shoot Them Up Game. All Right Reserved 2022.

#pragma once

#include "CoreMinimal.h"
#include "Player/STUBaseCharacter.h"
#include "STUPlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USphereComponent;

UCLASS()
class ST_SHOOTTHEMUP_API ASTUPlayerCharacter : public ASTUBaseCharacter
{
	GENERATED_BODY()

public:
    ASTUPlayerCharacter(const FObjectInitializer& ObjectInit);

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    
    virtual bool IsRunning() const override;
    
protected:

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent* SpringArmComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "Components")
    USphereComponent* CameraCollisionComponent;

    virtual void BeginPlay() override;
    virtual void OnDeath() override;

private:
    
    bool WantsToRun = false;
    bool IsMovingForward = false;

    void MoveForward(float Amount);
    void MoveRight(float Amount);

    void OnStartRunning();
    void OnStopRunning();

    UFUNCTION()
    void OnCameraBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
    
    UFUNCTION()
    void OnCameraEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    void CheckCameraOverlap();
};
