// Fill out your copyright notice in the Description page of Project Settings.

#include "SneakCharacter.h"
#include "Classes/Components/CapsuleComponent.h"
#include "Classes/Components/SkeletalMeshComponent.h"
#include "DroneCharacter.h" 
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

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &ASneakCharacter::Shoot);
	PlayerInputComponent->BindAction("Swap", IE_Pressed, this, &ASneakCharacter::Swap);
}

void ASneakCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void ASneakCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void ASneakCharacter::Shoot()
{
	FHitResult HitResult;
	FCollisionQueryParams TraceParams;
	FVector ForwardVector = FPCameraComponent->GetForwardVector();

	FVector TraceStart = FPCameraComponent->GetComponentLocation();
	FVector TraceEnd = TraceStart + (ForwardVector * 5000.0f);
	
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Fired"));
	if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, TraceParams))
	{
		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Blue, false, 3.0f);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Hit: %s"), *(HitResult.Actor->GetName())));
		
		if (HitResult.GetActor() != nullptr)
		{
			FDamageEvent DamageEvent(UDamageType::StaticClass());
			float DamageAmount = 1.0f;
			HitResult.GetActor()->TakeDamage(DamageAmount, DamageEvent, GetController(), this);
		}

		// For box shenanigans
		if (HitResult.GetComponent()->IsSimulatingPhysics())
		{
			HitResult.GetComponent()->AddImpulseAtLocation(FVector(0.f,0.f,1.f) * 10000.0f, HitResult.Location);
		}
	}
}

void ASneakCharacter::Swap()
{
	// If this is the first time swapping, spawn the drone 
	ADroneCharacter* Drone = GetWorld()->SpawnActor<ADroneCharacter>(DroneClass, FVector(0.f,0.f,0.f), this->GetViewRotation());
	Drone->RegisterPlayer(this);
	if (Drone)
	{
		GetController()->Possess(Drone);
	}
}