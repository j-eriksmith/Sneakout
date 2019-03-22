// Fill out your copyright notice in the Description page of Project Settings.

#include "HunterController.h"
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
		RunBehaviorTree(BehaviorTree);
	}
}
