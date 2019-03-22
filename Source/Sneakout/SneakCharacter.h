// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Classes/Camera/CameraComponent.h"
#include "SneakCharacter.generated.h"

UCLASS()
class SNEAKOUT_API ASneakCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASneakCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input when Character is possessed by Controller
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION() // TODO: try without these
	void MoveForward(float Value);

	UFUNCTION()
	void MoveRight(float Value);

	UFUNCTION()
	void Shoot();

	UPROPERTY(VisibleAnywhere) // Non-editable value, but exposed in editor
	UCameraComponent* FPCameraComponent;

	UPROPERTY(VisibleDefaultsOnly) // Instances will not see this in-editor
	USkeletalMeshComponent* FPMesh;
};
