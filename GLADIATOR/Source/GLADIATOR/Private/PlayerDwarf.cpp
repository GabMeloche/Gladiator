// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerDwarf.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraComponent.h"
#include "Camera/CameraComponent.h"
#include "Containers/UnrealString.h"

APlayerDwarf::APlayerDwarf()
{
	AutoPossessPlayer = EAutoReceiveInput::Player0;

    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    m_cameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    m_cameraBoom->SetupAttachment(RootComponent);
    m_cameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
    m_cameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

    // Create a follow camera
    m_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    m_camera->SetupAttachment(m_cameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
    m_camera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

    GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
}

APlayerDwarf::~APlayerDwarf()
{
}

void APlayerDwarf::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_isDead)
	{
		if (!m_hasSentDeath)
		{
			m_playerDeathEvent.Broadcast();
			m_hasSentDeath = true;
		}
	}
}

void APlayerDwarf::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerDwarf::SetupDirections()
{
    FVector forwardVec = m_camera->GetForwardVector();
    forwardVec.Z = 0.0f;
    ForwardDirection = forwardVec * ForwardSpeed;

    FVector rightVector = m_camera->GetRightVector();
    rightVector.Z = 0.0f;
    RightDirection = rightVector * RightSpeed;
}

void APlayerDwarf::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &APlayerDwarf::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &APlayerDwarf::MoveRight);

    // We have 2 versions of the rotation bindings to handle different kinds of devices differently
    // "turn" handles devices that provide an absolute delta, such as a mouse.
    // "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
    PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis("TurnRate", this, &APlayerDwarf::TurnAtRate);
    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("LookUpRate", this, &APlayerDwarf::LookUpAtRate);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ADwarf::Jump);
	PlayerInputComponent->BindAction("LeftClick", IE_Pressed, this, &ADwarf::Attack);
	PlayerInputComponent->BindAction("RightClick", IE_Pressed, this, &ADwarf::Block);
	PlayerInputComponent->BindAction("RightClick", IE_Released, this, &ADwarf::StopBlock);
}

void APlayerDwarf::MoveRight(float Value)
{
	if (!m_canMove)
		return;

    if ((Controller != NULL) && (Value != 0.0f))
    {
        // find out which way is right
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // get right vector 
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        // add movement in that direction
        AddMovementInput(Direction, Value);
    }
}

void APlayerDwarf::MoveForward(float Value)
{
	if (!m_canMove)
		return;

    if ((Controller != NULL) && (Value != 0.0f))
    {
        // find out which way is forward
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // get forward vector
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(Direction, Value);
    }
}

void APlayerDwarf::TurnAtRate(float Rate)
{
    // calculate delta for this frame from the rate information
    AddControllerYawInput(Rate * 45 * GetWorld()->GetDeltaSeconds());
}

void APlayerDwarf::LookUpAtRate(float Rate)
{
    // calculate delta for this frame from the rate information
    AddControllerPitchInput(Rate * 45 * GetWorld()->GetDeltaSeconds());
}
