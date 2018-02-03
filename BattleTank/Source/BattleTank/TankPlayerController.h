// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	ATank * GetControlledTank() const;
	
	virtual void BeginPlay() override;

	virtual void Tick(float) override;

private:

	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5f;

	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.33333f;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.f;

	//Start the tank barrel moving so that a shot would hit where the crosshair intersects the world
	void AimTowardsCrosshair();

	//Return an out parameter and true if hits landscape
	bool GetSightRayHitLocation(FVector &HitLocation) const;

};
