// Fill out your copyright notice in the Description page of Project Settings.

#include "HunterCharacter.h"

// Sets default values
AHunterCharacter::AHunterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHunterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

float AHunterCharacter::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	// Disable this lad
	
	return 0.0f;
}

// Called every frame
void AHunterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHunterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{


	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

