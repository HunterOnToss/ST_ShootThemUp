// Shoot Them Up Game. All Right Reserved 2022.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "STUAIController.generated.h"

class USTU_AIPerceptionComponent;

UCLASS()
class ST_SHOOTTHEMUP_API ASTUAIController : public AAIController
{
	GENERATED_BODY()

public:

    ASTUAIController();

protected:

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
    USTU_AIPerceptionComponent* STU_AIPerceptionComponent;
    
    virtual void OnPossess(APawn* InPawn) override;
    virtual void Tick(float DeltaSeconds) override;
};
