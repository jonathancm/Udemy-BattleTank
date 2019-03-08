// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

 // Forward Declaration
class UTankTurret;
class UTankBarrel;

// Holds barrel's properties
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	UTankAimingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	void AimAt(FVector WorldSpaceLocation, float LaunchSpeed);
	void MoveBarrelTowards(FVector AimDirection);
	
	void SetBarrelReference(UTankBarrel* BarrelToSet);
	void SetTurretReference(UTankTurret* TurretToSet);
	
private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
};
