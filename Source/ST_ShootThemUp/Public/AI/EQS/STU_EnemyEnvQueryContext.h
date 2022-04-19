// Shoot Them Up Game. All Right Reserved 2022.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "STU_EnemyEnvQueryContext.generated.h"

UCLASS()
class ST_SHOOTTHEMUP_API USTU_EnemyEnvQueryContext : public UEnvQueryContext
{
	GENERATED_BODY()

public:
    
    virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;

protected:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
    FName EnemyActorKeyName = "EnemyActor";
    
};
