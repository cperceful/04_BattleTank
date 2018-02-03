// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/World.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank * ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector OutHitLocation; //OUT parameter >:(
	if (GetSightRayHitLocation(OutHitLocation))
	{
		GetControlledTank()->AimAt(OutHitLocation);
		//Get world location if line-trace through crosshair
		//If it hits the landscape
			//Aim at this point
	}
	


}

bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const
{
	//Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D((ViewportSizeX * CrosshairXLocation), (ViewportSizeY * CrosshairYLocation));

	//"de-project" the screen position of the crosshair to a world postion
	FVector StartLocation;
	FVector LookDirection;

	bool bDeprojected = DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, StartLocation, LookDirection);

	if (bDeprojected)
	{
		//line trace along that direction aka look direction
		//see what we hit up to a maximum range
		FHitResult HitResult;
		FVector EndLocation = StartLocation + LookDirection * LineTraceRange;

		bool bHit = GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Visibility
		);
		if (bHit)
		{
			OutHitLocation = HitResult.Location;
			return true;
		}
	}
	OutHitLocation = FVector(0.f, 0.f, 0.f);
	return false;;
}
