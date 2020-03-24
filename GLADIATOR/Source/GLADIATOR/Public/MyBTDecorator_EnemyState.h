// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "MyBTDecorator_EnemyState.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATOR_API UMyBTDecorator_EnemyState : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()
public:
    virtual void OnNodeActivation(FBehaviorTreeSearchData& SearchData) override;
    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;
};
