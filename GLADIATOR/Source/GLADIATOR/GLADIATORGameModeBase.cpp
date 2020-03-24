// Fill out your copyright notice in the Description page of Project Settings.


#include "GLADIATORGameModeBase.h"
#include "TimerManager.h"
#include "EnemyManager.h"
#include "Engine/EngineTypes.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "PlayerDwarf.h"
#include "Engine/World.h"

AGLADIATORGameModeBase::AGLADIATORGameModeBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGLADIATORGameModeBase::BeginPlay()
{
	APlayerDwarf* player = Cast<APlayerDwarf>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (player)
		player->m_playerDeathEvent.AddDynamic(this, &AGLADIATORGameModeBase::OnPlayerDeath);

	TArray<AActor*> tmpMgr;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyManager::StaticClass(), tmpMgr);
	m_enemyManager = (AEnemyManager*)tmpMgr[0];

	m_playerWinEvent.AddDynamic(this, &AGLADIATORGameModeBase::OnPlayerWin);

}

// Called every frame
void AGLADIATORGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_enemyManager->CheckIfAllDead())
	{
		if (!m_sentWinConfirmation)
		{
			m_sentWinConfirmation = true;
			m_playerWinEvent.Broadcast();
		}
	}
}

void AGLADIATORGameModeBase::OnPlayerDeath()
{
	GetWorld()->GetTimerManager().SetTimer(m_timerHandleRestartLevel, this, &AGLADIATORGameModeBase::RestartLevel, m_timeToRestartLevel, true);
}

void AGLADIATORGameModeBase::OnPlayerWin()
{
	GetWorld()->GetTimerManager().SetTimer(m_timerHandleRestartLevel, this, &AGLADIATORGameModeBase::RestartLevel, m_timeToRestartLevel, true);
}

void AGLADIATORGameModeBase::RestartLevel()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}