// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"
#include "EnemyDwarf.h"
#include "GLADIATORGameModeBase.h"
#include "TimerManager.h"
#include "Engine/EngineTypes.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
AEnemyManager::AEnemyManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}


// Called when the game starts or when spawned
void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> foundEnemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyDwarf::StaticClass(), foundEnemies);

	for (auto& enemy : foundEnemies)
	{
		m_enemyDwarves.Add((AEnemyDwarf*)enemy);
		m_enemiesDead.Add(false);
	}
}

// Called every frame
void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_time += DeltaTime;

	if (m_canAttack && !CheckIfAllDead())
	{
		m_canAttack = false;

		int attackingDwarf = FMath::RandRange(0, m_enemyDwarves.Num() - 1);

		while (m_enemyDwarves[attackingDwarf]->GetIsDead())
		{
			attackingDwarf = FMath::RandRange(0, m_enemyDwarves.Num() - 1);
		}

		m_enemyDwarves[attackingDwarf]->SetMustAttack(true);

		GetWorld()->GetTimerManager().SetTimer(m_timerHandleAttacks, this, &AEnemyManager::SwitchCanAttack, m_timeBetweenAttacks, true);
	}
}

bool AEnemyManager::CheckIfAllDead()
{
	for (int i = 0; i < m_enemyDwarves.Num(); ++i)
	{
		m_enemiesDead[i] = m_enemyDwarves[i]->GetIsDead();
	}

	return !m_enemiesDead.Contains(false);
}

void AEnemyManager::SwitchCanAttack()
{
	m_canAttack = true;
}