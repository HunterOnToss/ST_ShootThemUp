// Shoot Them Up Game. All Right Reserved 2022.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "STUPlayerController.generated.h"

class USTURespawnComponent;

UCLASS()
class ST_SHOOTTHEMUP_API ASTUPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
    ASTUPlayerController();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
    USTURespawnComponent* RespawnComponent;
    
    virtual void OnPossess(APawn* InPawn) override;
};
