// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyDwarf.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "PlayerDwarf.h"
#include "Math/Vector.h"

AEnemyDwarf::AEnemyDwarf()
{
}
void AEnemyDwarf::BeginPlay()
{
	Super::BeginPlay();
	m_player = (APlayerDwarf*)(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (m_player)
		UE_LOG(LogTemp, Warning, TEXT("Enemy found player"));
}

void AEnemyDwarf::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_player &&
		m_player->m_isAttacking &&
		!m_isBlocking &&
		m_canBlock &&
		FVector::Dist(GetActorLocation(), m_player->GetActorLocation()) <= 150.0f)
	{
		m_canBlock = false;
		int chanceToBlock = FMath::RandRange(0, m_chanceToDefend);

		if (chanceToBlock % m_chanceToDefend == 0)
		{
			Block();
			GetWorld()->GetTimerManager().SetTimer(m_blockCooldownTimerHandle, this, &AEnemyDwarf::SwitchCanBlock, m_blockCooldown, true);
			GetWorld()->GetTimerManager().SetTimer(m_stopBlockTimerHandle, this, &ADwarf::StopBlock, 
				m_player->m_ColliderActivateTime + m_player->m_ColliderDeactivateTime, true);
		}
	}
}

void AEnemyDwarf::SwitchCanBlock()
{
	m_canBlock = true;
}
