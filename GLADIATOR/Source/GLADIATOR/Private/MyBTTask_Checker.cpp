// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_Checker.h"

EBTNodeResult::Type UMyBTTask_Checker::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

    UBlackboardComponent* m_blackboard = OwnerComp.GetBlackboardComponent();


    ACharacter* m_player = UGameplayStatics::GetPlayerCharacter(m_blackboard->GetWorld(), 0);
    APawn* m_AI = OwnerComp.GetAIOwner()->GetPawn();

    float Distance = FVector::Distance(m_player->GetActorLocation(), m_AI->GetActorLocation());
    m_blackboard->SetValueAsFloat("actual_range", Distance);
    m_blackboard->SetValueAsFloat("min_range", minRange);

    if (Distance > minRange)
        m_blackboard->SetValueAsInt("state", 0);
    
    if (Distance < minRange)
    {
        if(Distance < minRange - 40)
            m_blackboard->SetValueAsInt("state", -1);
        else
            m_blackboard->SetValueAsInt("state", 1);

    }
    

    return EBTNodeResult::Succeeded;
}

void UMyBTTask_Checker::Attack(ACharacter* p_player)
{
    m_blackboard->SetValueAsInt("state", 2);

}
