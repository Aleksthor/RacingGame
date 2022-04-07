// Fill out your copyright notice in the Description page of Project Settings.


#include "RacingEnemy.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerCar.h"

// Sets default values
ARacingEnemy::ARacingEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	// 23 Locations
	LocationsArray.Add(FVector(-1120.f, 1550.f, 21740.f));
	LocationsArray.Add(FVector(-1120.f, 1550.f, 21740.f));
	LocationsArray.Add(FVector(10320.f, 9100.f, 20610.f));
	LocationsArray.Add(FVector(26300.f, 13100.f, 15870.f));
	LocationsArray.Add( FVector(41990.f, 7960.f, 14530.f));
	LocationsArray.Add(FVector(39950.f, -8830.f, 13340.f));
	LocationsArray.Add(FVector(45320.f, -23420.f, 5880.f));
	LocationsArray.Add(FVector(22640.f, -24450.f, 5260.f));
	LocationsArray.Add(FVector(15300.f, -29670.f, 5110.f));
	LocationsArray.Add(FVector(14580.f, -36370.f, 5070.f));
	LocationsArray.Add(FVector(6860.f, -36640.f, 5380.f));
	LocationsArray.Add(FVector(-7700.f, -11400.f, 12140.f));
	LocationsArray.Add(FVector(-4990.f, -6260.f, 12260.f));
	LocationsArray.Add(FVector(6340.f, -6740.f, 12790.f));
	LocationsArray.Add(FVector(6340.f, -6740.f, 12790.f));
	LocationsArray.Add(FVector(15140.f, -5590.f, 13380.f));
	LocationsArray.Add(FVector(20340.f, 730.f, 15120.f));
	LocationsArray.Add(FVector(23680.f, -5890.f, 15430.f));
	LocationsArray.Add(FVector(36630.f, 820.f, 20180.f));
	LocationsArray.Add(FVector(30830.f, 6300.f, 22640.f));
	LocationsArray.Add(FVector(25550.f, 2710.f, 23260.f));
	LocationsArray.Add(FVector(2160.f, 7730.f, 25370.f));
	LocationsArray.Add(FVector(-14790.f, 14240.f, 22570.f));
	LocationsArray.Add(FVector(-15210.f, 6340.f, 22310.f));

}

// Called when the game starts or when spawned
void ARacingEnemy::BeginPlay()
{
	Super::BeginPlay();

	AIController = Cast<AAIController>(GetController());


	

	
	
}

// Called every frame
void ARacingEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	APlayerCar* Player = Cast<APlayerCar>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (Player)
	{
		if (Player->bGameStarted && !init)
		{
			init = true;
			MoveToLocation(LocationsArray[CurrentLocation]);
		}
	}


	float LengthFromNextArray = (LocationsArray[CurrentLocation] - GetActorLocation()).Size();

	if (LengthFromNextArray < 100.f)
	{
		CurrentLocation++;
		MoveToLocation(LocationsArray[CurrentLocation]);
	}

}

// Called to bind functionality to input
void ARacingEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ARacingEnemy::MoveToLocation(FVector Location)
{
	if (AIController)
	{
		FAIMoveRequest MoveRequest;

		MoveRequest.SetGoalLocation(Location);
		MoveRequest.SetAcceptanceRadius(200.f);

		FNavPathSharedPtr NavPath;
		AIController->MoveTo(MoveRequest, &NavPath);
	}
	
}

