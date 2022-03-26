// Copyright Epic Games, Inc. All Rights Reserved.


#include "RacingGameGameModeBase.h"
#include "CheckpointCollider.h"
#include "PlayerCar.h"
#include "Kismet/GameplayStatics.h"

ARacingGameGameModeBase::ARacingGameGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;


}

void ARacingGameGameModeBase::BeginPlay()
{



	if (UGameplayStatics::GetCurrentLevelName(GetWorld()) == "MOSSYMOOR")
	{

		UE_LOG(LogTemp, Warning, TEXT("PLayer Name: %s"), *PlayerName);
		APawn* Temp = GetWorld()->GetFirstPlayerController()->GetPawn();

		if (Temp)
		{
			Player = Cast<APlayerCar>(Temp);
		}
	
		UWorld* World = GetWorld();
		
		if (World )
		{

			//SpawnCheckpoints
			tempEnemy = World->SpawnActor<ACheckpointCollider>(CheckpointColliderBP, Checkpoint1Vector, Checkpoint1Rotator);
			CheckpointArray.Add(tempEnemy);

			tempEnemy = World->SpawnActor<ACheckpointCollider>(CheckpointColliderBP, Checkpoint2Vector, Checkpoint2Rotator);
			CheckpointArray.Add(tempEnemy);

			tempEnemy = World->SpawnActor<ACheckpointCollider>(CheckpointColliderBP, Checkpoint3Vector, Checkpoint3Rotator);
			CheckpointArray.Add(tempEnemy);

			tempEnemy = World->SpawnActor<ACheckpointCollider>(CheckpointColliderBP, Checkpoint4Vector, Checkpoint4Rotator);
			CheckpointArray.Add(tempEnemy);

			tempEnemy = World->SpawnActor<ACheckpointCollider>(CheckpointColliderBP, Checkpoint5Vector, Checkpoint5Rotator);
			CheckpointArray.Add(tempEnemy);

			tempEnemy = World->SpawnActor<ACheckpointCollider>(CheckpointColliderBP, Checkpoint6Vector, Checkpoint6Rotator);
			CheckpointArray.Add(tempEnemy);
	
			tempEnemy = World->SpawnActor<ACheckpointCollider>(CheckpointColliderBP, Checkpoint7Vector, Checkpoint7Rotator);
			CheckpointArray.Add(tempEnemy);

		
		
		}
	}
	
	

}

void ARacingGameGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!Player->bGameStarted)
	{
		PreGameClock += DeltaSeconds;

		if (PreGameClock > OneSecond)
		{
			PreGameClock = 0.f;
			SecondsUntilStart--;
		}
		if (SecondsUntilStart == 0)
		{
			Player->bGameStarted = true;
		}
	}

	



	if (UGameplayStatics::GetCurrentLevelName(GetWorld()) == "MOSSYMOOR")
	{

		switch (CurrentCheckpoint)
		{
		case 0:
			CheckpointArray[0]->isValid = true;
			break;
		case 1:
			CheckpointArray[1]->isValid = true;
			break;
		case 2:
			CheckpointArray[2]->isValid = true;
			break;
		case 3:
			CheckpointArray[3]->isValid = true;
			break;
		case 4:
			CheckpointArray[4]->isValid = true;
			break;
		case 5:
			CheckpointArray[5]->isValid = true;
			break;
		case 6:
			CheckpointArray[6]->isValid = true;
			break;
		}

		if (CurrentCheckpoint > 6)
		{
			GameWon();
		}
	}

	
}

void ARacingGameGameModeBase::GameWon()
{
	UE_LOG(LogTemp, Warning, TEXT("Game Won"));
	FString FinalTimer = Player->LastCheckPointTimer;
	Player->bGameOver = true;
	UE_LOG(LogTemp, Warning, TEXT("Time: %s"), *FinalTimer);
}

void ARacingGameGameModeBase::Reset()
{
}

void ARacingGameGameModeBase::LoadMap1()
{
	FName Level1 = FName("MOSSYMOOR");
	UGameplayStatics::OpenLevel(GetWorld(), Level1);
}
