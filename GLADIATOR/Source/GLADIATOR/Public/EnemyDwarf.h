// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dwarf.h"
#include "EnemyDwarf.generated.h"

UCLASS()
class GLADIATOR_API AEnemyDwarf : public ADwarf
{
	GENERATED_BODY()

public:
	AEnemyDwarf();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	inline int GetChanceToDefend() { return m_chanceToDefend; }

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float m_blockCooldown = 2.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int m_chanceToDefend = 3;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool m_canBlock = true;

private:

	void SwitchCanBlock();

	class APlayerDwarf* m_player;

	FTimerHandle m_blockCooldownTimerHandle;
	FTimerHandle m_stopBlockTimerHandle;

};
