// Shoot Them Up Game. All Right Reserved 2022.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "STUMenuPlayerController.generated.h"

UCLASS()
class ST_SHOOTTHEMUP_API ASTUMenuPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

    virtual void BeginPlay() override;
    
};
