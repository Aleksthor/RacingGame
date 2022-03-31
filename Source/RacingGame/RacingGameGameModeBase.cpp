// Copyright Epic Games, Inc. All Rights Reserved.


#include "RacingGameGameModeBase.h"
#include "CheckpointCollider.h"
#include "PlayerCar.h"
#include "Kismet/GameplayStatics.h"
#include "RacingSaveGame.h"
#include "SpeedBoosterv1.h"
#include "Target.h"

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
			tempCheckpoint = World->SpawnActor<ACheckpointCollider>(CheckpointColliderBP, Checkpoint1Vector, Checkpoint1Rotator);
			CheckpointArray.Add(tempCheckpoint);

			tempCheckpoint = World->SpawnActor<ACheckpointCollider>(CheckpointColliderBP, Checkpoint2Vector, Checkpoint2Rotator);
			CheckpointArray.Add(tempCheckpoint);

			tempCheckpoint = World->SpawnActor<ACheckpointCollider>(CheckpointColliderBP, Checkpoint3Vector, Checkpoint3Rotator);
			CheckpointArray.Add(tempCheckpoint);

			tempCheckpoint = World->SpawnActor<ACheckpointCollider>(CheckpointColliderBP, Checkpoint4Vector, Checkpoint4Rotator);
			CheckpointArray.Add(tempCheckpoint);

			tempCheckpoint = World->SpawnActor<ACheckpointCollider>(CheckpointColliderBP, Checkpoint5Vector, Checkpoint5Rotator);
			CheckpointArray.Add(tempCheckpoint);

			tempCheckpoint = World->SpawnActor<ACheckpointCollider>(CheckpointColliderBP, Checkpoint6Vector, Checkpoint6Rotator);
			CheckpointArray.Add(tempCheckpoint);
	

		
		
		}

		InitItems();
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
	if (CurrentLevel == Level1 && Player)
	{
		switch (CurrentRound)
		{
		case 1:
			if (CurrentCheckpoint > 5) // Means Round is Over | Then reset colliders
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
			/*	CheckpointArray[6]->isValid = false;
				CheckpointArray[6]->isHit = false;*/

				RespawnItems();

				CurrentCheckpoint = 0;
				Round1Time = Player->WorldTimer;
			}
			break;
		case 2:
			if (CurrentCheckpoint > 5) // Means Round is Over | Then reset colliders
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
			/*	CheckpointArray[6]->isValid = false;
				CheckpointArray[6]->isHit = false;*/

				RespawnItems();

				CurrentCheckpoint = 0;
				Round2Time = Player->WorldTimer - Round1Time;
			}
			break;
		case 3:
			if (CurrentCheckpoint > 5) // Means Round is Over | Then reset colliders
			{
				Round3Time = Player->WorldTimer - Round2Time;
				TotalTime = Player->WorldTimer;
				TotalPoints = Player->Points;
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
	/*	case 6:
			CheckpointArray[6]->isValid = true;*/
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
	/*	if (SaveInstance->Level1Stats.Section7Best > Section7BestTime || FMath::IsNearlyZero(SaveInstance->Level1Stats.Section7Best))
		{
			SaveInstance->Level1Stats.Section7Best = Section7BestTime;
		}*/

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
		//if (SaveInstance->Level1Stats.WorldCheckpoint7Best > WorldCheckpoint7 || FMath::IsNearlyZero(SaveInstance->Level1Stats.WorldCheckpoint7Best))
		//{
		//	SaveInstance->Level1Stats.WorldCheckpoint7Best = WorldCheckpoint7;
		//}
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
		//if (SaveInstance->Level1Stats.WorldCheckpoint14Best > WorldCheckpoint14 || FMath::IsNearlyZero(SaveInstance->Level1Stats.WorldCheckpoint14Best))
		//{
		//	SaveInstance->Level1Stats.WorldCheckpoint14Best = WorldCheckpoint14;
		//}
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
		//if (SaveInstance->Level1Stats.WorldCheckpoint21Best > WorldCheckpoint21 || FMath::IsNearlyZero(SaveInstance->Level1Stats.WorldCheckpoint21Best))
		//{
		//	SaveInstance->Level1Stats.WorldCheckpoint21Best = WorldCheckpoint21;
		//}
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
	/*	Section7BestTime = LoadInstance->Level1Stats.Section7Best;*/

		WorldCheckpoint1 = LoadInstance->Level1Stats.WorldCheckpoint1Best;
		WorldCheckpoint2 = LoadInstance->Level1Stats.WorldCheckpoint2Best;
		WorldCheckpoint3 = LoadInstance->Level1Stats.WorldCheckpoint3Best;
		WorldCheckpoint4 = LoadInstance->Level1Stats.WorldCheckpoint4Best;
		WorldCheckpoint5 = LoadInstance->Level1Stats.WorldCheckpoint5Best;
		WorldCheckpoint6 = LoadInstance->Level1Stats.WorldCheckpoint6Best;
		/*WorldCheckpoint7 = LoadInstance->Level1Stats.WorldCheckpoint7Best;*/
		WorldCheckpoint8 = LoadInstance->Level1Stats.WorldCheckpoint8Best;
		WorldCheckpoint9 = LoadInstance->Level1Stats.WorldCheckpoint9Best;
		WorldCheckpoint10 = LoadInstance->Level1Stats.WorldCheckpoint10Best;
		WorldCheckpoint11= LoadInstance->Level1Stats.WorldCheckpoint11Best;
		WorldCheckpoint12= LoadInstance->Level1Stats.WorldCheckpoint12Best;
		WorldCheckpoint13= LoadInstance->Level1Stats.WorldCheckpoint13Best;
		/*WorldCheckpoint14= LoadInstance->Level1Stats.WorldCheckpoint14Best;*/
		WorldCheckpoint15= LoadInstance->Level1Stats.WorldCheckpoint15Best;
		WorldCheckpoint16= LoadInstance->Level1Stats.WorldCheckpoint16Best;
		WorldCheckpoint17= LoadInstance->Level1Stats.WorldCheckpoint17Best;
		WorldCheckpoint18= LoadInstance->Level1Stats.WorldCheckpoint18Best;
		WorldCheckpoint19= LoadInstance->Level1Stats.WorldCheckpoint19Best;
		WorldCheckpoint20= LoadInstance->Level1Stats.WorldCheckpoint20Best;
		/*WorldCheckpoint21= LoadInstance->Level1Stats.WorldCheckpoint21Best;*/

		RoundBestTime = LoadInstance->Level1Stats.RoundBest;
		TotalBestTime = LoadInstance->Level1Stats.TotalBest;

		CurrentLevel = LoadInstance->Level1Stats.LevelName;
	}
	
	

}

void ARacingGameGameModeBase::InitItems()
{

	// SpeedBoosters

	UWorld* World = GetWorld();

	if (World)
	{
		tempSpeedBoost = World->SpawnActor<ASpeedBoosterv1>(SpeedboostBP, SpeedBoost1Vector, SpeedBoost1Rotator);
		SpeedBoostArray.Add(tempSpeedBoost);
		SpeedBoostArray[0]->SetActorHiddenInGame(false);
		SpeedBoostArray[0]->SetActorEnableCollision(true);

		tempSpeedBoost = World->SpawnActor<ASpeedBoosterv1>(SpeedboostBP, SpeedBoost2Vector, SpeedBoost2Rotator);
		SpeedBoostArray.Add(tempSpeedBoost);
		SpeedBoostArray[1]->SetActorHiddenInGame(false);
		SpeedBoostArray[1]->SetActorEnableCollision(true);

		tempSpeedBoost = World->SpawnActor<ASpeedBoosterv1>(SpeedboostBP, SpeedBoost3Vector, SpeedBoost3Rotator);
		SpeedBoostArray.Add(tempSpeedBoost);
		SpeedBoostArray[2]->SetActorHiddenInGame(false);
		SpeedBoostArray[2]->SetActorEnableCollision(true);

		tempSpeedBoost = World->SpawnActor<ASpeedBoosterv1>(SpeedboostBP, SpeedBoost4Vector, SpeedBoost4Rotator);
		SpeedBoostArray.Add(tempSpeedBoost);
		SpeedBoostArray[3]->SetActorHiddenInGame(false);
		SpeedBoostArray[3]->SetActorEnableCollision(true);

		tempSpeedBoost = World->SpawnActor<ASpeedBoosterv1>(SpeedboostBP, SpeedBoost5Vector, SpeedBoost5Rotator);
		SpeedBoostArray.Add(tempSpeedBoost);
		SpeedBoostArray[4]->SetActorHiddenInGame(false);
		SpeedBoostArray[4]->SetActorEnableCollision(true);

		tempSpeedBoost = World->SpawnActor<ASpeedBoosterv1>(SpeedboostBP, SpeedBoost6Vector, SpeedBoost6Rotator);
		SpeedBoostArray.Add(tempSpeedBoost);
		SpeedBoostArray[5]->SetActorHiddenInGame(false);
		SpeedBoostArray[5]->SetActorEnableCollision(true);

		tempSpeedBoost = World->SpawnActor<ASpeedBoosterv1>(SpeedboostBP, SpeedBoost7Vector, SpeedBoost7Rotator);
		SpeedBoostArray.Add(tempSpeedBoost);
		SpeedBoostArray[6]->SetActorHiddenInGame(false);
		SpeedBoostArray[6]->SetActorEnableCollision(true);

		tempSpeedBoost = World->SpawnActor<ASpeedBoosterv1>(SpeedboostBP, SpeedBoost8Vector, SpeedBoost8Rotator);
		SpeedBoostArray.Add(tempSpeedBoost);
		SpeedBoostArray[7]->SetActorHiddenInGame(false);
		SpeedBoostArray[7]->SetActorEnableCollision(true);

		tempSpeedBoost = World->SpawnActor<ASpeedBoosterv1>(SpeedboostBP, SpeedBoost9Vector, SpeedBoost9Rotator);
		SpeedBoostArray.Add(tempSpeedBoost);
		SpeedBoostArray[8]->SetActorHiddenInGame(false);
		SpeedBoostArray[8]->SetActorEnableCollision(true);

		tempSpeedBoost = World->SpawnActor<ASpeedBoosterv1>(SpeedboostBP, SpeedBoost10Vector, SpeedBoost10Rotator);
		SpeedBoostArray.Add(tempSpeedBoost);
		SpeedBoostArray[9]->SetActorHiddenInGame(false);
		SpeedBoostArray[9]->SetActorEnableCollision(true);




	}




	// Targets


	if (World)
	{
		
		tempTarget = World->SpawnActor<ATarget>(TargetBP, Target1Vector, Target1Rotator);
		TargetArray.Add(tempTarget);
		TargetArray[0]->SetActorHiddenInGame(false);
		TargetArray[0]->SetActorEnableCollision(true);

		tempTarget = World->SpawnActor<ATarget>(TargetBP, Target2Vector, Target2Rotator);
		TargetArray.Add(tempTarget);
		TargetArray[1]->SetActorHiddenInGame(false);
		TargetArray[1]->SetActorEnableCollision(true);

		tempTarget = World->SpawnActor<ATarget>(TargetBP, Target3Vector, Target3Rotator);
		TargetArray.Add(tempTarget);
		TargetArray[2]->SetActorHiddenInGame(false);
		TargetArray[2]->SetActorEnableCollision(true);

		tempTarget = World->SpawnActor<ATarget>(TargetBP, Target4Vector, Target4Rotator);
		TargetArray.Add(tempTarget);
		TargetArray[3]->SetActorHiddenInGame(false);
		TargetArray[3]->SetActorEnableCollision(true);

		tempTarget = World->SpawnActor<ATarget>(TargetBP, Target5Vector, Target5Rotator);
		TargetArray.Add(tempTarget);
		TargetArray[4]->SetActorHiddenInGame(false);
		TargetArray[4]->SetActorEnableCollision(true);

		tempTarget = World->SpawnActor<ATarget>(TargetBP, Target6Vector, Target6Rotator);
		TargetArray.Add(tempTarget);
		TargetArray[5]->SetActorHiddenInGame(false);
		TargetArray[5]->SetActorEnableCollision(true);

		tempTarget = World->SpawnActor<ATarget>(TargetBP, Target7Vector, Target7Rotator);
		TargetArray.Add(tempTarget);
		TargetArray[6]->SetActorHiddenInGame(false);
		TargetArray[6]->SetActorEnableCollision(true);

		tempTarget = World->SpawnActor<ATarget>(TargetBP, Target8Vector, Target8Rotator);
		TargetArray.Add(tempTarget);
		TargetArray[7]->SetActorHiddenInGame(false);
		TargetArray[7]->SetActorEnableCollision(true);

		tempTarget = World->SpawnActor<ATarget>(TargetBP, Target9Vector, Target9Rotator);
		TargetArray.Add(tempTarget);
		TargetArray[8]->SetActorHiddenInGame(false);
		TargetArray[8]->SetActorEnableCollision(true);

		tempTarget = World->SpawnActor<ATarget>(TargetBP, Target10Vector, Target10Rotator);
		TargetArray.Add(tempTarget);
		TargetArray[9]->SetActorHiddenInGame(false);
		TargetArray[9]->SetActorEnableCollision(true);

		tempTarget = World->SpawnActor<ATarget>(TargetBP, Target11Vector, Target11Rotator);
		TargetArray.Add(tempTarget);
		TargetArray[10]->SetActorHiddenInGame(false);
		TargetArray[10]->SetActorEnableCollision(true);

		tempTarget = World->SpawnActor<ATarget>(TargetBP, Target12Vector, Target12Rotator);
		TargetArray.Add(tempTarget);
		TargetArray[11]->SetActorHiddenInGame(false);
		TargetArray[11]->SetActorEnableCollision(true);

		tempTarget = World->SpawnActor<ATarget>(TargetBP, Target13Vector, Target13Rotator);
		TargetArray.Add(tempTarget);
		TargetArray[12]->SetActorHiddenInGame(false);
		TargetArray[12]->SetActorEnableCollision(true);

		tempTarget = World->SpawnActor<ATarget>(TargetBP, Target14Vector, Target14Rotator);
		TargetArray.Add(tempTarget);
		TargetArray[13]->SetActorHiddenInGame(false);
		TargetArray[13]->SetActorEnableCollision(true);
		
	}

}

void ARacingGameGameModeBase::RespawnItems()
{

	for (int i{}; i < SpeedBoostArray.Num(); i++)
	{
		if (SpeedBoostArray[i]->isHit)
		{
			SpeedBoostArray[i]->SetActorEnableCollision(true);
			SpeedBoostArray[i]->SetActorHiddenInGame(false);
			SpeedBoostArray[i]->isHit = false;
		}
	}
	for (int i{}; i < TargetArray.Num(); i++)
	{
		if (TargetArray[i]->isHit)
		{
			TargetArray[i]->SetActorEnableCollision(true);
			TargetArray[i]->SetActorHiddenInGame(false);
			TargetArray[i]->isHit = false;
		}
	}
}
