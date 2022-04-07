// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RacingEnemy.generated.h"

UCLASS()
class RACINGGAME_API ARacingEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARacingEnemy();


	class AAIController* AIController{ nullptr };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



	void MoveToLocation(FVector Location);

	TArray<FVector> LocationsArray;

	int CurrentLocation = 0;

	bool MetNewLocation = false;
	bool init = false;
	// Vectors of Locations To Move To
	//FVector MoveTo1 = FVector(-1120.f, 1550.f, 21740.f);
	//FVector MoveTo2 = FVector(10320.f, 9100.f, 20610.f);
	//FVector MoveTo3 = FVector(26300.f, 13100.f, 15870.f);
	//FVector MoveTo4 = FVector(41990.f, 7960.f, 14530.f);
	//FVector MoveTo5 = FVector(39950.f,-8830.f, 13340.f);
	//FVector MoveTo6 = FVector(45320.f, -23420.f, 5880.f);
	//FVector MoveTo7 = FVector(22640.f, -24450.f, 5260.f);
	//FVector MoveTo8 = FVector(15300.f, -29670.f, 5110.f);
	//FVector MoveTo9 = FVector(14580.f, -36370.f, 5070.f);
	//FVector MoveTo10 = FVector(6860.f, -36640.f, 5380.f);
	//FVector MoveTo11 = FVector(-7700.f, -11400.f, 12140.f);
	//FVector MoveTo12 = FVector(-4990.f, -6260.f, 12260.f);
	//FVector MoveTo13 = FVector(6340.f, -6740.f, 12790.f);
	//FVector MoveTo14 = FVector(6340.f, -6740.f, 12790.f);
	//FVector MoveTo15 = FVector(15140.f, -5590.f, 13380.f);
	//FVector MoveTo16 = FVector(20340.f, 730.f, 15120.f);
	//FVector MoveTo17 = FVector(23680.f, -5890.f, 15430.f);
	//FVector MoveTo18 = FVector(36630.f, 820.f, 20180.f);
	//FVector MoveTo19 = FVector(30830.f, 6300.f, 22640.f);
	//FVector MoveTo20 = FVector(25550.f, 2710.f, 23260.f);
	//FVector MoveTo21 = FVector(2160.f, 7730.f, 25370.f);
	//FVector MoveTo22 = FVector(-14790.f, 14240.f, 22570.f);
	//FVector MoveTo23 = FVector(-15210.f, 6340.f, 22310.f);
	
};
