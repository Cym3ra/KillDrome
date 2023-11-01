// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/BaseBike.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


ABaseBike::ABaseBike()
{

	PrimaryActorTick.bCanEverTick = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;

}

void ABaseBike::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(VehicleContext, 0);
		}
	}
	
}

void ABaseBike::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseBike::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(ThrottleAction, ETriggerEvent::Triggered, this, &ABaseBike::ApplyThrottle);
		//EnhancedInputComponent->BindAction(ThrottleAction,ETriggerEvent::Completed, this, &ABaseBike::ApplyThrottle);
		EnhancedInputComponent->BindAction(SteeringAction, ETriggerEvent::Triggered, this, &ABaseBike::ApplySteering);
		//EnhancedInputComponent->BindAction(SteeringAction, ETriggerEvent::Completed, this, &ABaseBike::ApplySteering);

	}

}

void ABaseBike::ApplyThrottle(const FInputActionValue& Value)
{
	FRotator Rotation = Controller->GetControlRotation();
	FRotator Direction(0.0f, Rotation.Yaw, 0.0f);

	FVector ForwardDirection = FRotationMatrix(Direction).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, Value.Get<float>());
}

void ABaseBike::ApplySteering(const FInputActionValue& Value)
{
	FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
	float TurnValue = Value.Get<float>() * 0.6;
	FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightDirection, TurnValue);
	AddControllerYawInput(TurnValue);
}



