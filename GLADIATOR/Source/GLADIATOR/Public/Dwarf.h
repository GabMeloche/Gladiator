// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Dwarf.generated.h"

UCLASS()
class GLADIATOR_API ADwarf : public ACharacter
{
	GENERATED_BODY()

public:
	ADwarf();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable, Category = "Custom")
    virtual void Teleport(FVector p_vector);

    UFUNCTION(BlueprintCallable, Category = "Custom")
    virtual void MoveActor(FVector p_vector);

	UFUNCTION(BlueprintCallable, Category = "Custom")
	virtual void Attack();
	
	UFUNCTION(BlueprintCallable, Category = "Custom")
	virtual void Block();
	
	UFUNCTION(BlueprintCallable, Category = "Custom")
	virtual void StopBlock();

	UFUNCTION()
	void RevertDwarfColor();
	
	UFUNCTION()
	void ChangeShieldColor();

	UFUNCTION()
	inline bool GetIsDead() { return m_isDead; }

	UFUNCTION()
	void SetIsDead(bool p_isDead) { m_isDead = p_isDead; }

	UFUNCTION()
	inline bool GetMustAttack() { return m_mustAttack; }

	UFUNCTION()
	void SetMustAttack(bool p_mustAttack) { m_mustAttack = p_mustAttack; }

	UFUNCTION(BlueprintCallable, Category = "Custom")
	void OnWeaponHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION(BlueprintCallable, Category = "Custom")
	void OnShieldGetHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool m_isBlocking = false;
    
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool m_isAttacking = false;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool m_canMove = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int m_health = 3;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float m_speedMultiplier = 1.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float m_attackCooldown;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float m_ColliderActivateTime = 0.2f;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float m_ColliderDeactivateTime = 0.6f;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float m_TimeChangeColorWhenHit = 1.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UMaterial* m_shieldHitMaterial;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UMaterial* m_hammerHitMaterial;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<class UMaterialInterface*> m_originalMaterials;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class USkeletalMeshComponent* m_hammer;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class USkeletalMeshComponent* m_shield;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class UBoxComponent* m_box;
		
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class USphereComponent* m_shieldCollider;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class UParticleSystemComponent* m_shieldClash;


protected:
	bool m_canAttack = true;
	bool m_hasHit = false;
	bool m_isDead = false;
	bool m_mustAttack;
	int TriggerCountdown;
	float m_timeSinceAttack;
	float m_time;
	float m_attackTime;
	FTimerHandle m_getHitTimerHandle;
	FTimerHandle m_hitEnemyTimerHandle;

	void ChangeOtherDwarfsColor(ADwarf* p_other);
};
