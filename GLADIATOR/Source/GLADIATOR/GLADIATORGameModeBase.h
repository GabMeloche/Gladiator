// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GLADIATORGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerWinDelegate);
UCLASS()
class GLADIATOR_API AGLADIATORGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGLADIATORGameModeBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float m_timeToRestartLevel = 5.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle m_timerHandleRestartLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AEnemyManager* m_enemyManager;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnPlayerDeath();
	
	UFUNCTION()
		void OnPlayerWin();

	UFUNCTION()
		void RestartLevel();

	UPROPERTY(BlueprintAssignable, Category = Callback)
	FOnPlayerWinDelegate m_playerWinEvent;

private:
	bool m_sentWinConfirmation = false;
};
