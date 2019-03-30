// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "EndGameVolume.generated.h"

/**
 * 
 */
UCLASS()
class SNEAKOUT_API AEndGameVolume : public ATriggerVolume
{
	GENERATED_BODY()
	
public:
	AEndGameVolume();

	UFUNCTION()
	void EnterVolume(AActor* OverlappedActor, AActor* OtherActor);

};
