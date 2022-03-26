// Copyright Epic Games, Inc. All Rights Reserved.


#include "RacingGameGameModeBase.h"
#include "CheckpointCollider.h"
#include "PlayerCar.h"
#include "Kismet/GameplayStatics.h"
#include "RacingSaveGame.h"

ARacingGameGameModeBase::ARacingGameGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;


}

void ARacingGameGameModeBase::BeginPlay()
{


	LoadGame();
	CurrentLevel = UGameplayStatics::GetCurrentLevelName(GetWorld());

	if (CurrentLevel == Level1)
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

	



	if (CurrentLevel == Level1)
	{
		switch (CurrentRound)
		{
		case 1:
			if (CurrentCheckpoint > 6) // Means Round is Over | Then reset colliders
			{
				CurrentRound++;
				CheckpointArray[0]->isValid = true;
				CheckpointArray[0]->isHit = false;
				CheckpointArray[1]->isValid = false;
				CheckpointArray[1]->isHit = false;
				CheckpointArray[2]->isValid = false;
				CheckpointArray[2]->isHit = false;
				CheckpointArray[3]->isValid = false;
				CheckpointArray[3]->isHit = false;
				CheckpointArray[4]->isValid = false;
				CheckpointArray[4]->isHit = false;
				CheckpointArray[5]->isValid = false;
				CheckpointArray[5]->isHit = false;
				CheckpointArray[6]->isValid = false;
				CheckpointArray[6]->isHit = false;

				CurrentCheckpoint = 0;
				Round1Time = Player->WorldTimer;
			}
			break;
		case 2:
			if (CurrentCheckpoint > 6) // Means Round is Over | Then reset colliders
			{
				CurrentRound++;

				CheckpointArray[0]->isValid = true;
				CheckpointArray[0]->isHit = false;
				CheckpointArray[1]->isValid = false;
				CheckpointArray[1]->isHit = false;
				CheckpointArray[2]->isValid = false;
				CheckpointArray[2]->isHit = false;
				CheckpointArray[3]->isValid = false;
				CheckpointArray[3]->isHit = false;
				CheckpointArray[4]->isValid = false;
				CheckpointArray[4]->isHit = false;
				CheckpointArray[5]->isValid = false;
				CheckpointArray[5]->isHit = false;
				CheckpointArray[6]->isValid = false;
				CheckpointArray[6]->isHit = false;

				CurrentCheckpoint = 0;
				Round2Time = Player->WorldTimer - Round1Time;
			}
			break;
		case 3:
			if (CurrentCheckpoint > 6) // Means Round is Over | Then reset colliders
			{
				Round3Time = Player->WorldTimer - Round2Time;
				TotalTime = Player->WorldTimer;
				GameWon();
			}

			break;
		}



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
		default:
			break;
		}

	
	}

	
}

void ARacingGameGameModeBase::GameWon()
{
	SaveGame();
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
	UGameplayStatics::OpenLevel(GetWorld(), Level1Name);
}

void ARacingGameGameModeBase::SaveGame()
{

	// Getting a RacingSaveGame Instance
	URacingSaveGame* SaveInstance = Cast<URacingSaveGame>(UGameplayStatics::CreateSaveGameObject(URacingSaveGame::StaticClass()));

	if (SaveInstance)
	{
		SaveInstance->Level1Stats.LevelName = CurrentLevel;

	
	
		// Check all sections
		if (SaveInstance->Level1Stats.Section1Best > Section1BestTime || FMath::IsNearlyZero(SaveInstance->Level1Stats.Section1Best))
		{
			SaveInstance->Level1Stats.Section1Best = Section1BestTime;
		}
		if (SaveInstance->Level1Stats.Section2Best > Section2BestTime || FMath::IsNearlyZero(SaveInstance->Level1Stats.Section2Best))
		{
			SaveInstance->Level1Stats.Section2Best = Section2BestTime;
		}
		if (SaveInstance->Level1Stats.Section3Best > Section3BestTime || FMath::IsNearlyZero(SaveInstance->Level1Stats.Section3Best))
		{
			SaveInstance->Level1Stats.Section3Best = Section3BestTime;
		}
		if (SaveInstance->Level1Stats.Section4Best > Section4BestTime || FMath::IsNearlyZero(SaveInstance->Level1Stats.Section4Best))
		{	
			SaveInstance->Level1Stats.Section4Best = Section4BestTime;
		}
		if (SaveInstance->Level1Stats.Section5Best > Section5BestTime || FMath::IsNearlyZero(SaveInstance->Level1Stats.Section5Best))
		{
			SaveInstance->Level1Stats.Section5Best = Section5BestTime;
		}
		if (SaveInstance->Level1Stats.Section6Best > Section6BestTime || FMath::IsNearlyZero(SaveInstance->Level1Stats.Section6Best))
		{
			SaveInstance->Level1Stats.Section6Best = Section6BestTime;
		}
		if (SaveInstance->Level1Stats.Section7Best > Section7BestTime || FMath::IsNearlyZero(SaveInstance->Level1Stats.Section7Best))
		{
			SaveInstance->Level1Stats.Section7Best = Section7BestTime;
		}

		// Check all 3 rounds

		if (SaveInstance->Level1Stats.RoundBest > Round1Time || FMath::IsNearlyZero(SaveInstance->Level1Stats.RoundBest))
		{
			SaveInstance->Level1Stats.RoundBest = Round1Time;
		}

		if (SaveInstance->Level1Stats.RoundBest > Round2Time || FMath::IsNearlyZero(SaveInstance->Level1Stats.RoundBest))
		{
			SaveInstance->Level1Stats.RoundBest = Round2Time;
		}

		if (SaveInstance->Level1Stats.RoundBest > Round3Time || FMath::IsNearlyZero(SaveInstance->Level1Stats.RoundBest))
		{
			SaveInstance->Level1Stats.RoundBest = Round3Time;
		}

		// Check Total Time for all 3 rounds

		if (SaveInstance->Level1Stats.TotalBest > TotalTime || FMath::IsNearlyZero(SaveInstance->Level1Stats.TotalBest))
		{
			SaveInstance->Level1Stats.TotalBest = TotalTime;
		}

	}

	
	

	
	// Save Game to slot
	UGameplayStatics::SaveGameToSlot(SaveInstance, SaveInstance->PlayerName, SaveInstance->UserIndex);
	
	
}

void ARacingGameGameModeBase::LoadGame()
{

	// Getting a RacingSaveGame Instance
	URacingSaveGame* LoadInstance = Cast<URacingSaveGame>(UGameplayStatics::CreateSaveGameObject(URacingSaveGame::StaticClass()));

	LoadInstance = Cast<URacingSaveGame>(UGameplayStatics::LoadGameFromSlot(LoadInstance->PlayerName, LoadInstance->UserIndex));

	if (LoadInstance)
	{
		Section1BestTime = LoadInstance->Level1Stats.Section1Best;
		Section2BestTime = LoadInstance->Level1Stats.Section2Best;
		Section3BestTime = LoadInstance->Level1Stats.Section3Best;
		Section4BestTime = LoadInstance->Level1Stats.Section4Best;
		Section5BestTime = LoadInstance->Level1Stats.Section5Best;
		Section6BestTime = LoadInstance->Level1Stats.Section6Best;
		Section7BestTime = LoadInstance->Level1Stats.Section7Best;

		RoundBestTime = LoadInstance->Level1Stats.RoundBest;
		TotalBestTime = LoadInstance->Level1Stats.TotalBest;

		CurrentLevel = LoadInstance->Level1Stats.LevelName;
	}
	
	

}
