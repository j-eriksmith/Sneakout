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
#include "DrawDebugHelpers.h"

// Sets default values
ADroneCharacter::ADroneCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// grabs pointer to component of this pawn
	FPCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Drone_FPCamera")); 

	FPCameraComponent->SetupAttachment(GetCapsuleComponent());
	// Similar to localPosition 
	FPCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
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

void ADroneCharacter::RegisterPlayer(APawn* Player)
{
	if (!this->Player)
	{
		this->Player = Player;
	}
}

void ADroneCharacter::PossessedBy(AController* NewController)
{
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
	FHitResult HitResult;
	FCollisionQueryParams TraceParams;
	FVector ForwardVector = FPCameraComponent->GetForwardVector();

	FVector TraceStart = FPCameraComponent->GetComponentLocation();
	FVector TraceEnd = TraceStart + (ForwardVector * 5000.0f);
	
	if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, TraceParams))
	{
		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Blue, false, 3.0f);

		if (HitResult.GetActor() != nullptr)
		{
			FDamageEvent DamageEvent(UDamageType::StaticClass());
			float DamageAmount = 1.0f;
			HitResult.GetActor()->TakeDamage(DamageAmount, DamageEvent, GetController(), this);
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
	if (Player)
	{
		GetController()->Possess(Player);
	}
}
