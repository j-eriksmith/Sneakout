// Fill out your copyright notice in the Description page of Project Settings.

#include "AttnService.h"
#include "Engine/World.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UAttnService::UAttnService()
{
	NodeName = "AttnService";
	bNotifyTick = true;
}

void UAttnService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (!AIController)
	{
		AIController = Cast<AHunterController>(OwnerComp.GetAIOwner());
	}
	// Filter out other objects of this class
	// Todo: cache this out once found once
	if (ActorsToIgnore.Num() == 0)
	{
		TArray<AActor*> ResultDrones;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AIClass, ActorsToIgnore);
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), DroneClass, ResultDrones);
		ActorsToIgnore.Append(ResultDrones);
	}

	// Prepare params for sphere query
	TArray< struct FHitResult > HitResults;
	Location = AIController->GetPawn()->GetActorLocation();
	FVector TraceEnd = Location + FVector(0.f, 0.f, 15.f);

	// This could be a single trace, but leaving options open for now
	UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), Location, TraceEnd, DetectRange, DesiredObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::None, HitResults, true);

	if (HitResults.Num() == 0)
	{
		AIController->GetBlackboardComponent()->SetValueAsObject(TargetToFollow.SelectedKeyName, nullptr);
	}

	for (const FHitResult& HitResult : HitResults)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, HitResult.GetActor()->GetName());
		// Do a line trace to the found actor- can we see them?
		FHitResult SightHitResult;
		FVector SightTraceEnd = HitResult.GetActor()->GetActorLocation();
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActors(ActorsToIgnore);

		if (GetWorld()->LineTraceSingleByChannel(SightHitResult, Location, SightTraceEnd, ECC_Camera, QueryParams))
		{
			// We can see them, so set blackboard data on our AI's controller
			AIController->GetBlackboardComponent()->SetValueAsVector(TargetLocation.SelectedKeyName, SightHitResult.GetActor()->GetActorLocation());
			AIController->GetBlackboardComponent()->SetValueAsObject(TargetToFollow.SelectedKeyName, SightHitResult.GetActor());
		}
		else
		{
			// We can't see the target
			AIController->GetBlackboardComponent()->SetValueAsObject(TargetToFollow.SelectedKeyName, nullptr);
		}
	}
}