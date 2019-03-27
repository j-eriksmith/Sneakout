// Fill out your copyright notice in the Description page of Project Settings.

#include "CloseEnoughDecorator.h"
#include "HunterController.h"
#include "BehaviorTree/BlackboardComponent.h"

UCloseEnoughDecorator::UCloseEnoughDecorator()
{
	NodeName = "DankCloseEnoughDecorator";
	bNotifyTick = true;
}

bool UCloseEnoughDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8 * NodeMemory) const
{
	// Todo: pull state maniulation into a different callback
	// so there's not a cast every time this is calcualted
	AHunterController* AIController = Cast<AHunterController>(OwnerComp.GetAIOwner());
	FVector TargetLocation = Cast<AActor>(AIController->GetBlackboardComponent()->GetValueAsObject(TargetToFollow.SelectedKeyName))->GetActorLocation();
	FVector OurLocation = AIController->GetPawn()->GetActorLocation();

	UE_LOG(LogTemp, Warning, TEXT("distance: %f"), FVector::Dist(OurLocation, TargetLocation));
	return FVector::Dist(OurLocation, TargetLocation) >= FollowDistance;
	//return false;
}