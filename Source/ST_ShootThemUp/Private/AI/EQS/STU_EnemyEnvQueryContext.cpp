// Shoot Them Up Game. All Right Reserved 2022.


#include "AI/EQS/STU_EnemyEnvQueryContext.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

void USTU_EnemyEnvQueryContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
    const auto QueryOwner = Cast<AActor>(QueryInstance.Owner.Get());
    const auto Blackboard = UAIBlueprintHelperLibrary::GetBlackboard(QueryOwner);
    if (Blackboard)
    {
        const auto ContextActor = Blackboard->GetValueAsObject(EnemyActorKeyName);
        UEnvQueryItemType_Actor::SetContextHelper(ContextData, Cast<AActor>(ContextActor));
        
    }    
    //Super::ProvideContext(QueryInstance, ContextData);    
}
