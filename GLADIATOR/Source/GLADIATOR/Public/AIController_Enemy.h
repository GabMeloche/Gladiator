// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Dwarf.h"
#include "AIController_Enemy.generated.h"
/**
 * 
 */
UCLASS()
class GLADIATOR_API AAIController_Enemy : public AAIController
{
	GENERATED_BODY()
public:

    virtual void OnPossess(APawn* InPawn) override;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BehaviorTree)
    UBehaviorTree* m_behaviorTree;
    float distance;

    bool GetIsDead() { return Cast<ADwarf>(GetPawn())->GetIsDead(); }

    void SetMustAttack(bool p_value) 
    {
        if (Cast<ADwarf>(GetPawn()) != nullptr)
            Cast<ADwarf>(GetPawn())->SetMustAttack(p_value);
    }
    bool GetMustAttack() 
    { 
        if (GetPawn() != nullptr)
        {
            return Cast<ADwarf>(GetPawn())->GetMustAttack();
        }
        else
        {
            GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, "CANT CAST ENEMY");
            return false;
        }
    }
};
