// Fill out your copyright notice in the Description page of Project Settings.

#include "HunterCharacter.h"
#include "SneakCharacter.h"
#include "Components/CapsuleComponent.h"

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
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AHunterCharacter::OnOverlapBegin);
}

float AHunterCharacter::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	// Disable this lad
	Cast<AHunterController>(GetController())->SetCCState(CCState::Stunned);
	return 0.0f;
}

void AHunterCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ASneakCharacter* SneakPlayer = Cast<ASneakCharacter>(OtherActor);
	if (SneakPlayer)
	{
		SneakPlayer->ShowDefeatPopup();
	}
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

