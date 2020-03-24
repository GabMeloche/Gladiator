// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerDwarf.h"
#include "EnemyManager.generated.h"

UCLASS()
class GLADIATOR_API AEnemyManager : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AEnemyManager();

	bool CheckIfAllDead();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void SwitchCanAttack();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float m_timeBetweenAttacks = 5.0f;


	FTimerHandle m_timerHandleAttacks;

private:
	TArray<class AEnemyDwarf*> m_enemyDwarves;
	TArray<bool> m_enemiesDead;
	float m_timeToFinishAttack;
	float m_time;
	bool m_canAttack = true;
	bool m_sentWinConfirmation = false;
};
