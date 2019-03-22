// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "HunterController.generated.h"

/**
 * 
 */
UCLASS()
class SNEAKOUT_API AHunterController : public AAIController
{
	GENERATED_BODY()

public:
	AHunterController();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	UBlackboardData* BlackboardData;

	UPROPERTY(EditDefaultsOnly)
	UBehaviorTree* BehaviorTree;
};
