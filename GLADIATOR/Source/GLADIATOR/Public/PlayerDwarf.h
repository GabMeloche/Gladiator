// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dwarf.h"
#include "PlayerDwarf.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDeathDelegate);

UCLASS()
class GLADIATOR_API APlayerDwarf : public ADwarf
{
    GENERATED_BODY()

private:
    APlayerDwarf();
    ~APlayerDwarf();

public:

    void Tick(float DeltaTime);
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UFUNCTION()
    void SetupDirections();
    UFUNCTION()
    void MoveRight(float Value);
    UFUNCTION()
    void MoveForward(float Value);
    UFUNCTION()
    void LookUpAtRate(float Rate);
    UFUNCTION()
    void TurnAtRate(float Rate);

	class UCameraComponent* GetCamera() { return m_camera; }

	UPROPERTY(BlueprintAssignable, Category = Callback)
	FOnPlayerDeathDelegate m_playerDeathEvent;

protected:
    void BeginPlay();

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCameraComponent* m_camera;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USpringArmComponent* m_cameraBoom;

    FVector ForwardDirection;
    FVector RightDirection;

    FRotator CamRot;
    float ForwardSpeed;
    float RightSpeed;
	bool m_hasSentDeath = false;
};
