// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!ensure(LeftTrackToSet && RightTrackToSet))
		return;

	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}


/*
* Fly-By-Wire control scheme
*/
void UTankMovementComponent::IntendAccelerate(float Throw)
{
	if (!ensure(LeftTrack && RightTrack))
		return;

	if (FMath::Abs(Throw) < 0.01f)
		return;

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurn(float Throw)
{
	if (!ensure(LeftTrack && RightTrack))
		return;

	if (FMath::Abs(Throw) < 0.01f)
		return;

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

/*
* AI Control Mapping
*/
void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector AIForwardIntention = MoveVelocity.GetSafeNormal();

	float AccelerationThrow = FVector::DotProduct(AIForwardIntention, TankForward);
	IntendAccelerate(AccelerationThrow);

	float TurnThrow = FVector::CrossProduct(AIForwardIntention, TankForward).Z;
	IntendTurn(TurnThrow);
}