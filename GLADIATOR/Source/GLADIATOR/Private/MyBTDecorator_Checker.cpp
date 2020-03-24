// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTDecorator_Checker.h"
#include "Engine/Engine.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

bool UMyBTDecorator_Checker::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    if (OwnerComp.GetBlackboardComponent() != nullptr)
        return OwnerComp.GetBlackboardComponent()->GetValueAsBool(m_bool);
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Blue, "NULLPTR");
        return false;
    }
}
