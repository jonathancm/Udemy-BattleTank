// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"


void UTankTurret::Rotate(float RelativeSpeed)
{
	// Rotate barrel, amount this frame given max elevation speed
	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.0f, +1.0f);

	float RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float RawNewRotation = RelativeRotation.Yaw + RotationChange;

	SetRelativeRotation(FRotator(0.0f, RawNewRotation, 0.0f));
}

