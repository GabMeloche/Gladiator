// Fill out your copyright notice in the Description page of Project Settings.


#include "Move_To_Dest.h"
EBTNodeResult::Type UMove_To_Dest::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    FVector player_pos;
    FVector enemy_pos;

    m_blackboard = OwnerComp.GetBlackboardComponent();

    ACharacter* m_player = UGameplayStatics::GetPlayerCharacter(m_blackboard->GetWorld(), 0);
    APawn* m_AI = OwnerComp.GetAIOwner()->GetPawn();

    player_pos = m_player->GetActorLocation();
    enemy_pos = m_AI->GetActorLocation();

    EPathFollowingRequestResult::Type result;

    result = OwnerComp.GetAIOwner()->MoveToLocation(player_pos, 60);

        return EBTNodeResult::Succeeded;
}