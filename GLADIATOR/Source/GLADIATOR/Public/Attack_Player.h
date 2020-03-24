// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "AIController_Enemy.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "Attack_Player.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATOR_API UAttack_Player : public UBTTaskNode
{
	GENERATED_BODY()

public:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
    UBlackboardComponent* m_blackboard;
};
