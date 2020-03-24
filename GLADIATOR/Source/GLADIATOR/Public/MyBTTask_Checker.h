// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "MyBTTask_Checker.generated.h"
/**
 * 
 */
UCLASS()
class GLADIATOR_API UMyBTTask_Checker : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
    void Attack(ACharacter* p_player);

    UBlackboardComponent* m_blackboard;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float minRange;

    uint8 in_range;
    uint8 actual_range;
};
