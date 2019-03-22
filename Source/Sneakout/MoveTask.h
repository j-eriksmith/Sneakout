// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "HunterController.h"
#include "MoveTask.generated.h"

/**
 * 
 */
UCLASS()
class SNEAKOUT_API UMoveTask : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UMoveTask();

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector TargetToFollow;

	UPROPERTY(EditAnywhere)
	float StopRadius = 400.f;

	AHunterController* AIController;

	APawn* AIControlledPawn;
protected:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
