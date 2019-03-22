// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "HunterController.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "AttnService.generated.h"

/**
 * 
 */
UCLASS()
class SNEAKOUT_API UAttnService : public UBTService
{
	GENERATED_BODY()
public:
	UAttnService();
	
	UPROPERTY(EditAnywhere)
	TArray<TEnumAsByte<EObjectTypeQuery>> DesiredObjectTypes;

	UPROPERTY(VisibleAnywhere)
	FVector Location;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector TargetToFollow;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector TargetLocation;

	UPROPERTY(EditAnywhere)
	UClass* AIClass;
	
	UPROPERTY(EditAnywhere)
	float DetectRange = 600.f;
	
	AHunterController* AIController;

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
