// Fill out your copyright notice in the Description page of Project Settings.


#include "Attack_Player.h"

EBTNodeResult::Type UAttack_Player::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (Cast<ADwarf>(OwnerComp.GetAIOwner()->GetPawn()) != nullptr)
    {
        if (OwnerComp.GetBlackboardComponent()->GetValueAsFloat("actual_range") < 120)
        {
            GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Orange, "Attacking");
            Cast<ADwarf>(OwnerComp.GetAIOwner()->GetPawn())->Attack();
            Cast<AAIController_Enemy>(OwnerComp.GetAIOwner())->SetMustAttack(false);
            return EBTNodeResult::Succeeded;
        }
    }
    return EBTNodeResult::Succeeded;
}