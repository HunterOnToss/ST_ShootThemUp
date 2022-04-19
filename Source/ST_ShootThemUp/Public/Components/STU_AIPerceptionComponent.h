// Shoot Them Up Game. All Right Reserved 2022.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "STU_AIPerceptionComponent.generated.h"

UCLASS()
class ST_SHOOTTHEMUP_API USTU_AIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()

public:

    AActor* GetClosestEnemy() const;
	
};
