// Shoot Them Up Game. All Right Reserved 2022.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvQueryTest_PickupCouldBeTaken.generated.h"


UCLASS()
class ST_SHOOTTHEMUP_API UEnvQueryTest_PickupCouldBeTaken : public UEnvQueryTest
{
	GENERATED_BODY()

public:
    UEnvQueryTest_PickupCouldBeTaken(const FObjectInitializer& ObjectInitializer);
    virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
};
