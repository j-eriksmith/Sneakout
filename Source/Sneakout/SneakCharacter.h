// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Classes/Camera/CameraComponent.h"
#include "DroneCharacter.h" 
#include "UserWidget.h"
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

	ADroneCharacter * Drone;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input when Character is possessed by Controller
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void ShowWinPopup();

	UFUNCTION() 
	void MoveForward(float Value);

	UFUNCTION()
	void MoveRight(float Value);

	UFUNCTION()
	void Swap();

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FPCameraComponent;

	UPROPERTY(VisibleDefaultsOnly) 
	USkeletalMeshComponent* FPMesh;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ADroneCharacter> DroneClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> WinMenu;

	UUserWidget* WinMenuHandle;
};
