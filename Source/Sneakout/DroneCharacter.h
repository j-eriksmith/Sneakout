// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Classes/Camera/CameraComponent.h"
#include "DroneCharacter.generated.h"

UCLASS()
class SNEAKOUT_API ADroneCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADroneCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	APawn * Player;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FPCameraComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;

	void RegisterPlayer(APawn* Player);

	UFUNCTION() 
	void MoveForward(float Value);

	UFUNCTION()
	void MoveRight(float Value);
	
	UFUNCTION()
	void Shoot();

	UFUNCTION()
	void Swap();
};
