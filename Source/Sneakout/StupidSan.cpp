// Fill out your copyright notice in the Description page of Project Settings.

#include "StupidSan.h"

// Sets default values
AStupidSan::AStupidSan()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called every frame
void AStupidSan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Location = GetActorLocation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	Location.Z += DeltaHeight * Magnitude;
	RunningTime += DeltaTime;
	SetActorLocation(Location);
}

