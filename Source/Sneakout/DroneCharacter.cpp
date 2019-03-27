// Fill out your copyright notice in the Description page of Project Settings.

#include "DroneCharacter.h"
#include "Components/InputComponent.h"

// Sets default values
ADroneCharacter::ADroneCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

	PlayerInputComponent->BindAction("Swap", IE_Pressed, this, &ADroneCharacter::Swap);
}

void ADroneCharacter::RegisterPlayer(APawn * Player)
{
	if (!this->Player)
	{
		this->Player = Player;
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

void ADroneCharacter::Swap()
{
	// Player is registered
	if (Player)
	{
		GetController()->Possess(Player);
	}
}

