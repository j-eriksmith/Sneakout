// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "HunterController.generated.h"

UENUM(BlueprintType)
enum class CCState : uint8 
{
	Stunned UMETA(DisplayName = "Stunned"),
	None UMETA(DisplayName = "None"),
};


UCLASS()
class SNEAKOUT_API AHunterController : public AAIController
{
	GENERATED_BODY()

public:
	AHunterController();

	void SetCCState(CCState State);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	UBlackboardData* BlackboardData;

	UPROPERTY(EditDefaultsOnly)
	UBehaviorTree* BehaviorTree;

	UFUNCTION()
	void ResetCCState();
	
	FTimerHandle StunTimerHandle;
};
