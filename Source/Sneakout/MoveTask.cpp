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

	AIController = Cast<AHunterController>(OwnerComp.GetAIOwner());

	AActor* MoveTarget = Cast<AActor>(AIController->GetBlackboardComponent()->GetValueAsObject(TargetToFollow.SelectedKeyName));
	EPathFollowingRequestResult::Type MoveResult = AIController->MoveToActor(MoveTarget, StopRadius, false);
	switch (MoveResult)
	{
		case EPathFollowingRequestResult::RequestSuccessful:
			return EBTNodeResult::InProgress;
		case EPathFollowingRequestResult::AlreadyAtGoal:
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
		default:
			return EBTNodeResult::Failed;
	}
}


