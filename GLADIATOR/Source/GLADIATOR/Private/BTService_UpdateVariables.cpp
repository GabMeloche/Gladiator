// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UpdateVariables.h"
#include "Engine/Engine.h"

void UBTService_UpdateVariables::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    //GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, "Service Working");
    AAIController* enemy = OwnerComp.GetAIOwner();

    ACharacter* player = UGameplayStatics::GetPlayerCharacter(OwnerComp.GetWorld(), 0);

    if (player != nullptr && enemy != nullptr)
    {
        float distance = FVector::Dist(player->GetActorLocation(), enemy->GetPawn()->GetActorLocation());
        OwnerComp.GetBlackboardComponent()->SetValueAsFloat("actual_range", distance);
        OwnerComp.GetBlackboardComponent()->SetValueAsBool("must_attack", Cast<AAIController_Enemy>(enemy)->GetMustAttack());
        OwnerComp.GetBlackboardComponent()->SetValueAsBool("is_dead", Cast<AAIController_Enemy>(enemy)->GetIsDead());
    }
    else
    {
        if (player == nullptr)
            GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Blue, "player is null");

        if (enemy == nullptr)
            GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Blue, "enemy is null");
    }
}