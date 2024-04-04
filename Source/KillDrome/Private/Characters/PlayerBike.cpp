// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerBike.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "HUD/BikeHUD.h"
#include "HUD/MainOverlay.h"
#include "Actors/Attributes.h"
#include "Kismet/GameplayStatics.h"

APlayerBike::APlayerBike()
{
	PrimaryActorTick.bCanEverTick = true;
	
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->SetupAttachment(GetRootComponent());
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetMesh());
	SpringArm->TargetArmLength = 450.f;
	SpringArm->SetRelativeLocation(FVector(-165.f, 0.f, 200.f));
	SpringArm->SetRelativeRotation(FRotator(-10.f, 0.f, 0.f));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void APlayerBike::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		InitializeOverlay(PlayerController);
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(VehicleContext, 0);
		}
	}
}

void APlayerBike::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	UpdateGameTimer();
}

void APlayerBike::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(ThrottleAction, ETriggerEvent::Triggered, this, &APlayerBike::ApplyThrottle);
		//EnhancedInputComponent->BindAction(ThrottleAction,ETriggerEvent::Completed, this, &ABaseBike::ApplyThrottle);
		EnhancedInputComponent->BindAction(SteeringAction, ETriggerEvent::Triggered, this, &APlayerBike::ApplySteering);
		//EnhancedInputComponent->BindAction(SteeringAction, ETriggerEvent::Completed, this, &ABaseBike::ApplySteering);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &APlayerBike::Fire);
	}
}

void APlayerBike::InitializeOverlay(APlayerController* PlayerController)
{
	ABikeHUD* BikeHUD = Cast<ABikeHUD>(PlayerController->GetHUD());
	if (BikeHUD)
	{
		MainOverlay = BikeHUD->GetBikeOverlay();
		SetHUDHealth();
		MainOverlay->SetEnemiesToKill(Attributes->GetEnemiesToKill());
	}
}

void APlayerBike::UpdateGameTimer()
{
	if (MainOverlay)
	{
		uint32 SecondsLeft = FMath::CeilToInt(TimeRemaining - GetWorld()->GetTimeSeconds());
		if (CountDownInt != SecondsLeft)
		{
			MainOverlay->SetCountDownText(TimeRemaining - GetWorld()->GetTimeSeconds());
		}
		
		CountDownInt = SecondsLeft;

		if (SecondsLeft <= 0)
		{
			MainOverlay->SetCountDownText(0);
			HandleGameOver();
		}
	}
}

void APlayerBike::HandleGameOver()
{
	MainOverlay->SetGameOverText();
	Attributes->SetPlayerInputDisabled();
	FTimerHandle LoadLevelTimer;
	GetWorldTimerManager().SetTimer(LoadLevelTimer, this, &APlayerBike::LoadMenu, LoadLevelDelay, false);
}

void APlayerBike::SetHUDHealth()
{
	if (MainOverlay && Attributes)
	{
		MainOverlay->SetHealthBarPercent(Attributes->GetHealthPercent());
	}
}

void APlayerBike::AddEnemiesKilled(int32 EnemiesKilled)
{
	if (Attributes && MainOverlay)
	{
		Attributes->AddEnemiesKilled(EnemiesKilled);
		MainOverlay->SetEnemiesKilled(Attributes->GetEnemiesKilled());
	}
}

void APlayerBike::AddEnemiesToEliminate()
{
	if (Attributes && MainOverlay)
	{
		MainOverlay->SetEnemiesToKill(Attributes->GetEnemiesLeftToKill());
	}
}

bool APlayerBike::CheckIfWon()
{
	if (Attributes)
	{
		if (Attributes->HasKilledEnoughEnemies())
		{
			return true;
		}
	}
	return false;
}

bool APlayerBike::TeleportTo(const FVector& DestLocation, const FRotator& DestRotation, bool bIsATest, bool bNoCheck)
{
	return Super::TeleportTo(DestLocation, DestRotation, bIsATest, bNoCheck);
}

void APlayerBike::LoadMenu()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("MainMenu"));
}

void APlayerBike::SetWinText()
{
	if(MainOverlay)
	{
		MainOverlay->SetWinText();
	}
}

void APlayerBike::UnsetWinText()
{
	if (MainOverlay)
	{
		MainOverlay->HideWinText();
	}
}

void APlayerBike::HandleDeath()
{
	Super::HandleDeath();
	TeleportTo(RespawnLocation, GetActorRotation(), false, false);
	
	if (MainOverlay && Attributes)
	{
		Attributes->ResetHealth();
		MainOverlay->SetHealthBarPercent(Attributes->GetHealthPercent());
	}
}

void APlayerBike::ApplyThrottle(const FInputActionValue& Value)
	{
	FRotator Rotation = Controller->GetControlRotation();
	FRotator Direction(0.0f, Rotation.Yaw, 0.0f);

	FVector ForwardDirection = FRotationMatrix(Direction).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, Value.Get<float>());
	}

	void APlayerBike::ApplySteering(const FInputActionValue& Value)
	{
	FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
	float TurnValue = Value.Get<float>() * 0.8;
	FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightDirection, TurnValue);
	AddControllerYawInput(TurnValue);
	}





