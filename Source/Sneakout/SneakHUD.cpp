// Fill out your copyright notice in the Description page of Project Settings.

#include "SneakHUD.h"
#include "Engine/Canvas.h"

void ASneakHUD::DrawHUD()
{
	Super::DrawHUD();

	FVector2D Center(Canvas->ClipX * .5f, Canvas->ClipY * .5f);
	FVector2D CrosshairPosition(Center.X - (CrosshairTexture->GetSurfaceWidth() * .5f), Center.Y - (CrosshairTexture->GetSurfaceHeight() * .5f));

	// Todo: play around with different colors, blendmode
	FCanvasTileItem TileItem(CrosshairPosition, CrosshairTexture->Resource, FColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(TileItem);
}