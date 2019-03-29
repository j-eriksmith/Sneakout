// Fill out your copyright notice in the Description page of Project Settings.

#include "SneakCharacter.h"
#include "Classes/Components/CapsuleComponent.h"
#include "Classes/Components/SkeletalMeshComponent.h"
#include "Engine.h"

// Sets default values
ASneakCharacter::ASneakCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// grabs pointer to component of this pawn
	FPCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FPCamera")); 

	FPCameraComponent->SetupAttachment(GetCapsuleComponent());
	// Similar to localPosition 
	FPCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
	FPCameraComponent->bUsePawnControlRotation = true;
	// create first person mesh
	FPMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FPMesh"));
	FPMesh->SetOnlyOwnerSee(true);

	// By default, this will parent to the root Capsule Component
	FPMesh->SetupAttachment(FPCameraComponent);
	FPMesh->CastShadow = false;

}

// Called when the game starts or when spawned
void ASneakCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetMesh()->SetOwnerNoSee(true);
}

// Called every frame
void ASneakCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASneakCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Delegates grabbed from .h file
	PlayerInputComponent->BindAxis("MoveForward", this, &ASneakCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASneakCharacter::MoveRight);

	// Since these pawn functions take one param - value - we can route them straight through BindAxis
	PlayerInputComponent->BindAxis("Turn", this, &ASneakCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ASneakCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Swap", IE_Pressed, this, &ASneakCharacter::Swap);
}

void ASneakCharacter::PossessedBy(AController* NewController)
{
}

void ASneakCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void ASneakCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void ASneakCharacter::Swap()
{
	// If this is the first time swapping, spawn the drone 
	if (!Drone)
	{
		Drone = GetWorld()->SpawnActor<ADroneCharacter>(DroneClass, FVector(0.f,0.f,0.f), this->GetViewRotation());
		Drone->RegisterPlayer(this);
	}
	if (Drone)
	{
		GetController()->Possess(Drone);
	}
}