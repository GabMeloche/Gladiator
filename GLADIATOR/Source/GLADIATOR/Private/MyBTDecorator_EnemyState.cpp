// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTDecorator_EnemyState.h"
#include "Engine/Engine.h"

void UMyBTDecorator_EnemyState::OnNodeActivation(FBehaviorTreeSearchData& SearchData)
{
    //UE_LOG(LogTemp, Warning, TEXT("LE DECORATOR QUI FONCITONNE TROP BIEN"));
    
}

bool UMyBTDecorator_EnemyState::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, "BONJOUR");
    return false;
}
