// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "MyBTDecorator_Checker.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATOR_API UMyBTDecorator_Checker : public UBTDecorator
{
    GENERATED_BODY()

private:
        FBlackboardKeySelector boolean_to_check;
public:
        virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

        UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FName m_bool;
        
};
