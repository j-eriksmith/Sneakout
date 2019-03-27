// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "CloseEnoughDecorator.generated.h"

/**
 * 
 */
UCLASS()
class SNEAKOUT_API UCloseEnoughDecorator : public UBTDecorator
{
	GENERATED_BODY()

public:
	UCloseEnoughDecorator();

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector TargetToFollow;

	UPROPERTY(EditAnywhere)
	float FollowDistance;

protected:
	bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8 * NodeMemory) const override;
};