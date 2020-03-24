// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "AIController_Enemy.h"
#include "GameFramework/Character.h"
#include "Move_To_Dest.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATOR_API UMove_To_Dest : public UBTTaskNode
{
	GENERATED_BODY()

private:
    UBlackboardComponent* m_blackboard;
public:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
