// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Classes/Camera/CameraComponent.h"
#include "UserWidget.h"
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

	UPROPERTY(EditDefaultsOnly)
	float ShootRange = 500.0f;

	FTimerHandle ShootCDHandle;

	bool bCanShoot = true;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void RegisterPlayer(APawn * Player);

	UFUNCTION() 
	void MoveForward(float Value);

	UFUNCTION()
	void MoveRight(float Value);
	
	UFUNCTION()
	void Shoot();

	UFUNCTION()
	void Swap();

	UFUNCTION()
	void ResetShootCD();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float ShootCD = 2.0f;

	UPROPERTY(BlueprintReadOnly)
	float ShootCurrentCD = ShootCD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> DroneHUD;

	UUserWidget* DroneHUDHandle;
};
