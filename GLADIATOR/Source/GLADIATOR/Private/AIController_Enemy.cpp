// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController_Enemy.h"
#include "Engine/Engine.h"

void AAIController_Enemy::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, "STARTING BEHAVIOR TREE");
    RunBehaviorTree(m_behaviorTree);
}