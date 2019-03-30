// Fill out your copyright notice in the Description page of Project Settings.

#include "EndGameVolume.h"
#include "Engine/World.h"
#include "SneakCharacter.h"
#include "SneakoutGameModeBase.h"

AEndGameVolume::AEndGameVolume()
{
	OnActorBeginOverlap.AddDynamic(this, &AEndGameVolume::EnterVolume);
}

void AEndGameVolume::EnterVolume(AActor* OverlappedActor, AActor* OtherActor)
{
	ASneakCharacter* Player = Cast<ASneakCharacter>(OtherActor);
	if (Player)
	{
		Player->ShowWinPopup();
	}
}
