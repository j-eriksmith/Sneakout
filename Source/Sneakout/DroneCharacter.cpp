// Fill out your copyright notice in the Description page of Project Settings.

#include "DroneCharacter.h"
#include "Components/InputComponent.h"
#include "CollisionQueryParams.h"
#include "Engine/World.h"
#include "GameFramework/DamageType.h"
#include "GameFramework/Controller.h"
#include "Engine/EngineTypes.h"
#include "Components/PrimitiveComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"

// Sets default values
ADroneCharacter::ADroneCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// grabs pointer to component of this pawn
	FPCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Drone_FPCamera")); 

	FPCameraComponent->SetupAttachment(GetCapsuleComponent());
	// Similar to localPosition 
	FPCameraComponent->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void ADroneCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADroneCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!bCanShoot && ShootCurrentCD > 0.0f)
	{
		ShootCurrentCD -= DeltaTime;
	}
}

// Called to bind functionality to input
void ADroneCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ADroneCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADroneCharacter::MoveRight);

	// Since these pawn functions take one param - value - we can route them straight through BindAxis
	PlayerInputComponent->BindAxis("Turn", this, &ADroneCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ADroneCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &ADroneCharacter::Shoot);
	PlayerInputComponent->BindAction("Swap", IE_Pressed, this, &ADroneCharacter::Swap);
}

void ADroneCharacter::RegisterPlayer(APawn * Player)
{
	this->Player = Player;
	
	if (DroneHUD && !DroneHUDHandle)
	{
		APlayerController* PC = Cast<APlayerController>(GetController());
		DroneHUDHandle = CreateWidget<UUserWidget>(GetWorld(), DroneHUD);
	}
	if (DroneHUDHandle && !bCanShoot)
	{
		DroneHUDHandle->AddToViewport();
	}
}

void ADroneCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void ADroneCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void ADroneCharacter::Shoot()
{
	if (!bCanShoot) return;

	FHitResult HitResult;
	FCollisionQueryParams TraceParams;
	FVector ForwardVector = FPCameraComponent->GetForwardVector();

	FVector TraceStart = FPCameraComponent->GetComponentLocation();
	FVector TraceEnd = TraceStart + (ForwardVector * ShootRange);
	
	if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, TraceParams))
	{

		if (HitResult.GetActor() != nullptr)
		{
			DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Blue, false, 5.0f);
			FDamageEvent DamageEvent(UDamageType::StaticClass());
			float DamageAmount = 1.0f;
			HitResult.GetActor()->TakeDamage(DamageAmount, DamageEvent, GetController(), this);

			// Start cooldown timer on hit
			bCanShoot = false;
			GetWorld()->GetTimerManager().SetTimer(ShootCDHandle, this, &ADroneCharacter::ResetShootCD, ShootCD, false);
			if (DroneHUDHandle)
			{
				DroneHUDHandle->AddToViewport();
			}
		}

		// For box shenanigans
		if (HitResult.GetComponent()->IsSimulatingPhysics())
		{
			HitResult.GetComponent()->AddImpulseAtLocation(FVector(0.f, 0.f, 1.f) * 10000.0f, HitResult.Location);
		}
	}
}

void ADroneCharacter::Swap()
{
	// Player is registered
	if (DroneHUDHandle)
	{
		DroneHUDHandle->RemoveFromViewport();
	}
	if (Player)
	{
		GetController()->Possess(Player);
	}
}

void ADroneCharacter::ResetShootCD()
{
	bCanShoot = true;
	ShootCurrentCD = ShootCD;
	if (DroneHUDHandle)
	{
		DroneHUDHandle->RemoveFromViewport();
	}
}
