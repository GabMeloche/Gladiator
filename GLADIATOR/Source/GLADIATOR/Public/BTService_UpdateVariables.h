// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "AIController_Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "BTService_UpdateVariables.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATOR_API UBTService_UpdateVariables : public UBTService
{
    GENERATED_BODY()

public:
    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    FName must_attack;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    FName is_dead;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    float minRange;
};
