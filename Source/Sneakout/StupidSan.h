// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StupidSan.generated.h"

UCLASS()
class SNEAKOUT_API AStupidSan : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStupidSan();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	uint32 Magnitude;
	float RunningTime; 
};
