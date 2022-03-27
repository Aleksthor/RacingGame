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


	CurrentRoundFunction();

	
}

void ARacingGameGameModeBase::CurrentRoundFunction()
{
	if (CurrentLevel == Level1)
	{
		switch (CurrentRound)
		{
		case 1:
			if (CurrentCheckpoint > 6) // Means Round is Over | Then reset colliders
			{
				RespawnItems();
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
				RespawnItems();
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
	Player->bGameOver = true;

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



		if (SaveInstance->Level1Stats.WorldCheckpoint1Best > WorldCheckpoint1 || FMath::IsNearlyZero(SaveInstance->Level1Stats.WorldCheckpoint1Best))
		{
			SaveInstance->Level1Stats.WorldCheckpoint1Best = WorldCheckpoint1;
		}
		if (SaveInstance->Level1Stats.WorldCheckpoint2Best > WorldCheckpoint2 || FMath::IsNearlyZero(SaveInstance->Level1Stats.WorldCheckpoint2Best))
		{
			SaveInstance->Level1Stats.WorldCheckpoint2Best = WorldCheckpoint2;
		}
		if (SaveInstance->Level1Stats.WorldCheckpoint3Best > WorldCheckpoint3 || FMath::IsNearlyZero(SaveInstance->Level1Stats.WorldCheckpoint3Best))
		{
			SaveInstance->Level1Stats.WorldCheckpoint3Best = WorldCheckpoint3;
		}
		if (SaveInstance->Level1Stats.WorldCheckpoint4Best > WorldCheckpoint4 || FMath::IsNearlyZero(SaveInstance->Level1Stats.WorldCheckpoint4Best))
		{
			SaveInstance->Level1Stats.WorldCheckpoint4Best = WorldCheckpoint4;
		}
		if (SaveInstance->Level1Stats.WorldCheckpoint5Best > WorldCheckpoint5 || FMath::IsNearlyZero(SaveInstance->Level1Stats.WorldCheckpoint5Best))
		{
			SaveInstance->Level1Stats.WorldCheckpoint5Best = WorldCheckpoint5;
		}
		if (SaveInstance->Level1Stats.WorldCheckpoint6Best > WorldCheckpoint6 || FMath::IsNearlyZero(SaveInstance->Level1Stats.WorldCheckpoint6Best))
		{
			SaveInstance->Level1Stats.WorldCheckpoint6Best = WorldCheckpoint6;
		}
		if (SaveInstance->Level1Stats.WorldCheckpoint7Best > WorldCheckpoint7 || FMath::IsNearlyZero(SaveInstance->Level1Stats.WorldCheckpoint7Best))
		{
			SaveInstance->Level1Stats.WorldCheckpoint7Best = WorldCheckpoint7;
		}
		if (SaveInstance->Level1Stats.WorldCheckpoint8Best > WorldCheckpoint8 || FMath::IsNearlyZero(SaveInstance->Level1Stats.WorldCheckpoint8Best))
		{
			SaveInstance->Level1Stats.WorldCheckpoint8Best = WorldCheckpoint8;
		}
		if (SaveInstance->Level1Stats.WorldCheckpoint9Best > WorldCheckpoint9 || FMath::IsNearlyZero(SaveInstance->Level1Stats.WorldCheckpoint9Best))
		{
			SaveInstance->Level1Stats.WorldCheckpoint9Best = WorldCheckpoint9;
		}
		if (SaveInstance->Level1Stats.WorldCheckpoint10Best > WorldCheckpoint10 || FMath::IsNearlyZero(SaveInstance->Level1Stats.WorldCheckpoint10Best))
		{
			SaveInstance->Level1Stats.WorldCheckpoint10Best = WorldCheckpoint10;
		}
		if (SaveInstance->Level1Stats.WorldCheckpoint11Best > WorldCheckpoint11 || FMath::IsNearlyZero(SaveInstance->Level1Stats.WorldCheckpoint11Best))
		{
			SaveInstance->Level1Stats.WorldCheckpoint11Best = WorldCheckpoint11;
		}
		if (SaveInstance->Level1Stats.WorldCheckpoint12Best > WorldCheckpoint12 || FMath::IsNearlyZero(SaveInstance->Level1Stats.WorldCheckpoint12Best))
		{
			SaveInstance->Level1Stats.WorldCheckpoint12Best = WorldCheckpoint12;
		}
		if (SaveInstance->Level1Stats.WorldCheckpoint13Best > WorldCheckpoint13 || FMath::IsNearlyZero(SaveInstance->Level1Stats.WorldCheckpoint13Best))
		{
			SaveInstance->Level1Stats.WorldCheckpoint13Best = WorldCheckpoint13;
		}
		if (SaveInstance->Level1Stats.WorldCheckpoint14Best > WorldCheckpoint14 || FMath::IsNearlyZero(SaveInstance->Level1Stats.WorldCheckpoint14Best))
		{
			SaveInstance->Level1Stats.WorldCheckpoint14Best = WorldCheckpoint14;
		}
		if (SaveInstance->Level1Stats.WorldCheckpoint15Best > WorldCheckpoint15 || FMath::IsNearlyZero(SaveInstance->Level1Stats.WorldCheckpoint15Best))
		{
			SaveInstance->Level1Stats.WorldCheckpoint15Best = WorldCheckpoint15;
		}
		if (SaveInstance->Level1Stats.WorldCheckpoint16Best > WorldCheckpoint16 || FMath::IsNearlyZero(SaveInstance->Level1Stats.WorldCheckpoint16Best))
		{
			SaveInstance->Level1Stats.WorldCheckpoint16Best = WorldCheckpoint16;
		}
		if (SaveInstance->Level1Stats.WorldCheckpoint17Best > WorldCheckpoint17 || FMath::IsNearlyZero(SaveInstance->Level1Stats.WorldCheckpoint17Best))
		{
			SaveInstance->Level1Stats.WorldCheckpoint17Best = WorldCheckpoint17;
		}
		if (SaveInstance->Level1Stats.WorldCheckpoint18Best > WorldCheckpoint18 || FMath::IsNearlyZero(SaveInstance->Level1Stats.WorldCheckpoint18Best))
		{
			SaveInstance->Level1Stats.WorldCheckpoint18Best = WorldCheckpoint18;
		}
		if (SaveInstance->Level1Stats.WorldCheckpoint19Best > WorldCheckpoint19 || FMath::IsNearlyZero(SaveInstance->Level1Stats.WorldCheckpoint19Best))
		{
			SaveInstance->Level1Stats.WorldCheckpoint19Best = WorldCheckpoint19;
		}
		if (SaveInstance->Level1Stats.WorldCheckpoint20Best > WorldCheckpoint20 || FMath::IsNearlyZero(SaveInstance->Level1Stats.WorldCheckpoint20Best))
		{
			SaveInstance->Level1Stats.WorldCheckpoint20Best = WorldCheckpoint20;
		}
		if (SaveInstance->Level1Stats.WorldCheckpoint21Best > WorldCheckpoint21 || FMath::IsNearlyZero(SaveInstance->Level1Stats.WorldCheckpoint21Best))
		{
			SaveInstance->Level1Stats.WorldCheckpoint21Best = WorldCheckpoint21;
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

		WorldCheckpoint1 = LoadInstance->Level1Stats.WorldCheckpoint1Best;
		WorldCheckpoint2 = LoadInstance->Level1Stats.WorldCheckpoint2Best;
		WorldCheckpoint3 = LoadInstance->Level1Stats.WorldCheckpoint3Best;
		WorldCheckpoint4 = LoadInstance->Level1Stats.WorldCheckpoint4Best;
		WorldCheckpoint5 = LoadInstance->Level1Stats.WorldCheckpoint5Best;
		WorldCheckpoint6 = LoadInstance->Level1Stats.WorldCheckpoint6Best;
		WorldCheckpoint7 = LoadInstance->Level1Stats.WorldCheckpoint7Best;
		WorldCheckpoint8 = LoadInstance->Level1Stats.WorldCheckpoint8Best;
		WorldCheckpoint9 = LoadInstance->Level1Stats.WorldCheckpoint9Best;
		WorldCheckpoint10 = LoadInstance->Level1Stats.WorldCheckpoint10Best;
		WorldCheckpoint11= LoadInstance->Level1Stats.WorldCheckpoint11Best;
		WorldCheckpoint12= LoadInstance->Level1Stats.WorldCheckpoint12Best;
		WorldCheckpoint13= LoadInstance->Level1Stats.WorldCheckpoint13Best;
		WorldCheckpoint14= LoadInstance->Level1Stats.WorldCheckpoint14Best;
		WorldCheckpoint15= LoadInstance->Level1Stats.WorldCheckpoint15Best;
		WorldCheckpoint16= LoadInstance->Level1Stats.WorldCheckpoint16Best;
		WorldCheckpoint17= LoadInstance->Level1Stats.WorldCheckpoint17Best;
		WorldCheckpoint18= LoadInstance->Level1Stats.WorldCheckpoint18Best;
		WorldCheckpoint19= LoadInstance->Level1Stats.WorldCheckpoint19Best;
		WorldCheckpoint20= LoadInstance->Level1Stats.WorldCheckpoint20Best;
		WorldCheckpoint21= LoadInstance->Level1Stats.WorldCheckpoint21Best;

		RoundBestTime = LoadInstance->Level1Stats.RoundBest;
		TotalBestTime = LoadInstance->Level1Stats.TotalBest;

		CurrentLevel = LoadInstance->Level1Stats.LevelName;
	}
	
	

}

void ARacingGameGameModeBase::RespawnItems()
{
}
