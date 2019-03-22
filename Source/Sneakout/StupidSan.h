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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere) // This is like a nuanced version of Unity's editor visibility- SerializeField-private, ReadOnly-public
	uint32 magnitude;
	float RunningTime; // PascalCase conventions for public members? C# boys
};
