// Fill out your copyright notice in the Description page of Project Settings.

#include "MoveTask.h"
#include "BehaviorTree/BlackboardComponent.h"

UMoveTask::UMoveTask()
{
	NodeName = "HuntTask";
}

EBTNodeResult::Type UMoveTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!AIController)
	{
		AIController = Cast<AHunterController>(OwnerComp.GetAIOwner());
		AIControlledPawn = AIController->GetPawn();
	}

	AActor* MoveTarget = Cast<AActor>(AIController->GetBlackboardComponent()->GetValueAsObject(TargetToFollow.SelectedKeyName));
	EPathFollowingRequestResult::Type MoveResult = AIController->MoveToActor(MoveTarget, StopRadius, false);
	switch (MoveResult)
	{
		case EPathFollowingRequestResult::RequestSuccessful:
			UE_LOG(LogTemp, Warning, TEXT("In Progress"));
			return EBTNodeResult::InProgress;
		case EPathFollowingRequestResult::AlreadyAtGoal:
			UE_LOG(LogTemp, Warning, TEXT("Task is at Goal"));
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
		default:
			UE_LOG(LogTemp, Warning, TEXT("Default Case - Failed"));
			return EBTNodeResult::Failed;
	}
	
}
