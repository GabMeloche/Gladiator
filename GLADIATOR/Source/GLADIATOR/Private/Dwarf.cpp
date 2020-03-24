// Fill out your copyright notice in the Description page of Project Settings.


#include "Dwarf.h"
#include "EnemyDwarf.h"
#include "Engine/EngineTypes.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Materials/MaterialInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/WorldPSCPool.h"

// Sets default values
ADwarf::ADwarf()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_hammer = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Hammer"));
	m_hammer->AttachTo(GetMesh(), "WeaponPoint");

	m_shield = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Shield"));
	m_shield->AttachTo(GetMesh(), "b_LeftHand");

	m_box = CreateDefaultSubobject<UBoxComponent>(TEXT("HammerBoxCollider"));
	m_box->OnComponentBeginOverlap.AddDynamic(this, &ADwarf::OnWeaponHit);
	m_box->SetupAttachment(m_hammer);

	m_shieldCollider = CreateDefaultSubobject<USphereComponent>(TEXT("ShieldSphereCollider"));
	m_shieldCollider->OnComponentBeginOverlap.AddDynamic(this, &ADwarf::OnShieldGetHit);
	m_shieldCollider->SetupAttachment(m_shield);

	m_hammerHitMaterial = CreateDefaultSubobject<UMaterial>(TEXT("HammerHitMaterial"));
	m_shieldHitMaterial = CreateDefaultSubobject<UMaterial>(TEXT("ShieldHitMaterial"));
}

// Called when the game starts or when spawned
void ADwarf::BeginPlay()
{
	Super::BeginPlay();
	m_box->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	m_shieldCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	m_originalMaterials = GetMesh()->GetMaterials();
}

void ADwarf::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	m_time += DeltaTime;

	if (m_isAttacking)
	{
		m_canAttack = false;

		m_attackTime += DeltaTime;

		// time period where collision box is activated and character movement is stopped
		if (m_attackTime > m_ColliderActivateTime && m_attackTime < m_ColliderDeactivateTime
			&& !m_hasHit)
		{
			m_canMove = false;
			m_box->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		}
		else
		{
			m_canMove = true;
			m_box->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}

		//Reset state after cooldown
		if (m_attackTime > m_attackCooldown)
		{
			m_isAttacking = false;
			m_canAttack = true;
			m_hasHit = false;
			m_attackTime = 0.0f;
		}
	}

	if (!m_isDead && m_health <= 0)
	{
		m_isDead = true;
		m_canMove = false;
		m_canAttack = false;
		m_box->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ADwarf::Teleport(FVector p_vector)
{
	SetActorLocation(p_vector);
}

void ADwarf::MoveActor(FVector p_vector)
{
	if (m_isAttacking || !m_canMove)
		return;

	AddMovementInput(p_vector, m_speedMultiplier);
}

void ADwarf::Attack()
{
	if (m_canAttack)
	{
		m_isAttacking = true;
	}
}

void ADwarf::OnWeaponHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == (AActor*)this)
		return;

	if (Cast<AEnemyDwarf>(this) && Cast<AEnemyDwarf>(OtherActor))
		return;

	if (OtherActor->IsA(ADwarf::StaticClass()))
	{
		m_hasHit = true;

		UE_LOG(LogTemp, Warning, TEXT("%s"), *OverlappedComp->GetName());
		ADwarf* other = Cast<ADwarf>(OtherActor);

		if (!other->m_isBlocking)
			--other->m_health;

		if (!other->m_isBlocking)
		{
			ChangeOtherDwarfsColor(other);
		}
	}
}

void ADwarf::RevertDwarfColor()
{
	for (int i = 0; i < m_originalMaterials.Num(); ++i)
	{
		GetMesh()->SetMaterial(i, m_originalMaterials[i]);
	}
}

void ADwarf::ChangeShieldColor()
{
	for (int i = 0; i < m_originalMaterials.Num(); ++i)
	{
		m_shield->SetMaterial(i, m_originalMaterials[i]);
	}
}

void ADwarf::OnShieldGetHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (m_isBlocking && Cast<ADwarf>(OtherActor)->m_isAttacking)
	{
		m_shield->SetMaterial(0, m_shieldHitMaterial);
		GetWorld()->GetTimerManager().SetTimer(m_getHitTimerHandle, this, &ADwarf::ChangeShieldColor, m_TimeChangeColorWhenHit, true);

		UE_LOG(LogTemp, Warning, TEXT("shield hit"));
	}
}

void ADwarf::ChangeOtherDwarfsColor(ADwarf* p_other)
{
	for (int i = 0; i < p_other->GetMesh()->GetMaterials().Num(); ++i)
	{
		p_other->GetMesh()->SetMaterial(i, m_hammerHitMaterial);
	}

	GetWorld()->GetTimerManager().SetTimer(m_hitEnemyTimerHandle, p_other, &ADwarf::RevertDwarfColor, m_TimeChangeColorWhenHit, true);
}

void ADwarf::Block()
{
	if (m_isAttacking)
		return;

	m_shieldCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	m_isBlocking = true;
	m_canAttack = false;
	m_canMove = false;
}

void ADwarf::StopBlock()
{
	m_box->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	m_isBlocking = false;
	m_canAttack = true;
	m_canMove = true;
}