// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/Pawn.h"
#include "TankAimingComponent.h"
#include "Tank.h" // To implement OnDeath

// Depends on Movement Component via AI Pathfinding System

ATankAIController::ATankAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	isAlive = true;
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent))
		return;
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank))
			return;

		// Subscribe our local method to the tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!AimingComponent)
		return;

	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn)
		return;

	MoveToActor(PlayerPawn, AcceptanceRadius);

	AimingComponent->AimAt(PlayerPawn->GetActorLocation());

	// Fire if ready
	if(AimingComponent->GetFiringState() == EFiringState::Locked)
		AimingComponent->Fire();
}

void ATankAIController::OnPossessedTankDeath()
{
	if (isAlive)
	{
		isAlive = false;
		
		auto PossessedTank = GetPawn();
		if (!(PossessedTank))
			return;
		
		PossessedTank->DetachFromControllerPendingDestroy();
	}
}
