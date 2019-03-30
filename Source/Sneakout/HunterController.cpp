// Fill out your copyright notice in the Description page of Project Settings.

#include "HunterController.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "BehaviorTree/BlackboardComponent.h"

AHunterController::AHunterController()
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
}

void AHunterController::BeginPlay()
{
	Super::BeginPlay();
	if (UseBlackboard(BlackboardData, Blackboard))
	{
		Blackboard->SetValueAsVector("Start", GetPawn()->GetActorLocation());
		Blackboard->SetValueAsFloat("StunDuration", 5.0f);
		Blackboard->SetValueAsFloat("SightAngle", 1.0472f);
		ResetCCState();
		RunBehaviorTree(BehaviorTree);
	}
}

void AHunterController::SetCCState(CCState State)
{
	float StunDuration = Blackboard->GetValueAsFloat("StunDuration");
	Blackboard->SetValueAsEnum("CCState", static_cast<uint8>(State));
	StopMovement();
	UWorld* World = GetWorld();
	if (World)
	{
		World->GetTimerManager().SetTimer(StunTimerHandle, this, &AHunterController::ResetCCState, StunDuration, false);
	}
}

void AHunterController::ResetCCState()
{
	Blackboard->SetValueAsEnum("CCState", static_cast<uint8>(CCState::None));
}
