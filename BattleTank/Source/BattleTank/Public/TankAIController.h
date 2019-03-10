// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ATankAIController();

protected:
	void BeginPlay() override;

public:
	void Tick(float DeltaTime) override;

	// How close the AI can get to the player
	float AcceptanceRadius = 3000.0f;

};
