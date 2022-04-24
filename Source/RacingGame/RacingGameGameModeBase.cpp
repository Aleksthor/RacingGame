// Copyright Epic Games, Inc. All Rights Reserved.


#include "RacingGameGameModeBase.h"
#include "CheckpointCollider.h"
#include "PlayerCar.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "RacingSaveGame.h"
#include "SpeedBoosterv1.h"
#include "Target.h"
#include "GameFramework/FloatingPawnMovement.h"


ARacingGameGameModeBase::ARacingGameGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;


}

void ARacingGameGameModeBase::BeginPlay()
{

	Super::BeginPlay();

	Saved = false;
	LoadGame();
	
	CurrentLevel = UGameplayStatics::GetCurrentLevelName(GetWorld());

	if (CurrentLevel == Level1)
	{

		
		APawn* Temp = GetWorld()->GetFirstPlayerController()->GetPawn();

		if (Temp)
		{
			Player = Cast<APlayerCar>(Temp);
		}
	
		if (Player)
		{
			if (!GameLoaded)
			{
				Player->FirstRun = true;
			}
			UWorld* World = GetWorld();

			if (World)
			{

				if (ShooterMode)
				{

					Player->SetActorLocation(FVector(-15000.f, 7550.f, 22210.f));
					Player->SetActorRotation(FRotator(0.f, 100.f, 0.f));
					Player->bCanNeverShoot = false;
					Cast<UFloatingPawnMovement>(Player->MovementComponent)->MaxSpeed = Player->PlayerMaxSpeed;
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

					InitItems();
				}
				else if (TimeAttack)
				{
					//UE_LOG(LogTemp, Warning, TEXT("TimeAttack"));
					Player->SetActorLocation(FVector(-15000.f, 7550.f, 22210.f));
					Player->SetActorRotation(FRotator(0.f, 280.f, 0.f));
					Player->bCanNeverShoot = true;
					Cast<UFloatingPawnMovement>(Player->MovementComponent)->MaxSpeed = 3500.f;
					//SpawnCheckpoints
					tempCheckpoint = World->SpawnActor<ACheckpointCollider>(CheckpointColliderBP, Checkpoint5Vector, Checkpoint5Rotator);
					CheckpointArray.Add(tempCheckpoint);

					tempCheckpoint = World->SpawnActor<ACheckpointCollider>(CheckpointColliderBP, Checkpoint4Vector, Checkpoint4Rotator);
					CheckpointArray.Add(tempCheckpoint);

					tempCheckpoint = World->SpawnActor<ACheckpointCollider>(CheckpointColliderBP, Checkpoint3Vector, Checkpoint3Rotator);
					CheckpointArray.Add(tempCheckpoint);

					tempCheckpoint = World->SpawnActor<ACheckpointCollider>(CheckpointColliderBP, Checkpoint2Vector, Checkpoint2Rotator);
					CheckpointArray.Add(tempCheckpoint);

					tempCheckpoint = World->SpawnActor<ACheckpointCollider>(CheckpointColliderBP, Checkpoint1Vector, Checkpoint1Rotator);
					CheckpointArray.Add(tempCheckpoint);

					tempCheckpoint = World->SpawnActor<ACheckpointCollider>(CheckpointColliderBP, Checkpoint6Vector, Checkpoint6Rotator);
					CheckpointArray.Add(tempCheckpoint);


					// Also spawn some boosters so we can gain more speed without shooting
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

					tempSpeedBoost = World->SpawnActor<ASpeedBoosterv1>(SpeedboostBP, SpeedBoost11Vector, SpeedBoost11Rotator);
					SpeedBoostArray.Add(tempSpeedBoost);
					SpeedBoostArray[10]->SetActorHiddenInGame(false);
					SpeedBoostArray[10]->SetActorEnableCollision(true);

					tempSpeedBoost = World->SpawnActor<ASpeedBoosterv1>(SpeedboostBP, SpeedBoost12Vector, SpeedBoost12Rotator);
					SpeedBoostArray.Add(tempSpeedBoost);
					SpeedBoostArray[11]->SetActorHiddenInGame(false);
					SpeedBoostArray[11]->SetActorEnableCollision(true);



				}


			}
		}

		

		
	}
	
	CurrentSectionBest = Section1BestTime;
	NextBest = WorldCheckpoint1;

}

void ARacingGameGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Pre Game Clock
	if (Player)
	{
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

	}


	// Switch function for current checkpoint/round
	CurrentRoundFunction();


	if (TimeAttack)
	{
		if (Player)
		{
			if (Player->bGameStarted)
			{
				DeathTimer -= DeltaSeconds;
			}

			if (DeathTimer < 0.f)
			{
				DeathTimer = 0.f;

				GameLost();

			}

		}
	}


	if (DeathTimerHUD)
	{
		ShowDeathClock += DeltaSeconds;
		if (ShowDeathClock > ShowDeathTimer)
		{
			DeathTimeAdded = "";
			DeathTimerHUD = false;
			ShowDeathClock = 0.f;
		}
	}

	
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
				
				Round3Time = Player->WorldTimer - Round2Time - Round1Time;


				BestRound = Round1Time;
				if (BestRound > Round2Time)
				{
					BestRound = Round2Time;
				}
				if (BestRound > Round3Time)
				{
					BestRound = Round3Time;
				}
				
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
	if (!Saved)
	{
		if (ShooterMode)
		{
			bGameWon = true;
			SwitchTimer();
			TotalPlayerScore = (TimeScore * TotalPoints) / 1000;

			if (TotalPlayerScore > 12000)
			{
				//UE_LOG(LogTemp, Warning, TEXT("Bronze Tier Achieved"));
				BronzeMedal = true;
				MainMenuShooterBronze++;
				HUDMedalString = "Bronze";
				if (GameWonSound)
				{
					UGameplayStatics::PlaySound2D(this, GameWonSound);
				}
			}
			if (TotalPlayerScore > 14000)
			{
				//UE_LOG(LogTemp, Warning, TEXT("Silver Tier Achieved"));
				SilverMedal = true;
				MainMenuShooterSilver++;
				HUDMedalString = "Silver";
				if (GameWonSound)
				{
					UGameplayStatics::PlaySound2D(this, GameWonSound);
				}
			}
			if (TotalPlayerScore > 16000)
			{
				//UE_LOG(LogTemp, Warning, TEXT("Gold Tier Achieved"));
				GoldMedal = true;
				MainMenuShooterGold++;
				HUDMedalString = "Gold";
				if (GameWonGoldSound)
				{
					UGameplayStatics::PlaySound2D(this, GameWonGoldSound);
				}
			}
			if (TotalPlayerScore > 22000)
			{
				UE_LOG(LogTemp, Warning, TEXT("Epic Tier Achieved"));
				EpicMedal = true;
				MainMenuShooterEpic++;
				HUDMedalString = "Epic";
				if (GameWonGoldSound)
				{
					UGameplayStatics::PlaySound2D(this, GameWonGoldSound);
				}
			}

			SaveGame();
			UE_LOG(LogTemp, Warning, TEXT("Game Won"));
			Player->bGameOver = true;
			Saved = true;
		}
		

		if (TimeAttack)
		{
			bGameWon = true;
			SaveGame();
			UE_LOG(LogTemp, Warning, TEXT("Game Won"));
			if (Player)
			{
				Player->bGameOver = true;
			}
			Saved = true;
		}
	}


}

void ARacingGameGameModeBase::GameLost()
{
	if (Player)
	{
		Player->bGameOver = true;
		Player->bDead = true;
	}
}

void ARacingGameGameModeBase::SwitchTimer()
{

	// calucluation done in Excel and here I set the values based on our sheet. // ( 1 / Time ) * 1000
	if (TotalTime < 480.f)
	{
		TimeScore = 2075;
	}
	if (TotalTime < 470.f)
	{
		TimeScore = 2125;
	}
	if (TotalTime < 460.f)
	{
		TimeScore = 2175;
	}
	if (TotalTime < 450.f)
	{
		TimeScore = 2225;
	}
	if (TotalTime < 440.f)
	{
		TimeScore = 2275;
	}
	 if (TotalTime < 430.f)
	{
		TimeScore = 2325;
	}
	 if (TotalTime < 420.f)
	{
		TimeScore = 2400;
	}
	 if (TotalTime < 410.f)
	{
		TimeScore = 2450;
	}
	 if (TotalTime < 400.f)
	{
		TimeScore = 2500;
	}
	 if (TotalTime < 390.f)
	{
		TimeScore = 2550;
	}
	 if (TotalTime < 380.f)
	{
		TimeScore = 2600;
	}
	 if (TotalTime < 370.f)
	{
		TimeScore = 2700;
	}
	 if (TotalTime < 360.f)
	{
		TimeScore = 2750;
	}
	 if (TotalTime < 350.f)
	{
		TimeScore = 2850;
	}
	if (TotalTime < 340.f)
	{
		TimeScore = 2950;
	}
	 if (TotalTime < 330.f)
	{
		TimeScore = 3025;
	}
	 if (TotalTime < 320.f)
	{
		TimeScore = 3125;
	}
	 if (TotalTime < 310.f)
	{
		TimeScore = 3250;
	}
	 if (TotalTime < 300.f)
	{
		TimeScore = 3350;
	}
	 if (TotalTime < 290.f)
	{
		TimeScore = 3450;
	}
	 if (TotalTime < 280.f)
	{
		TimeScore = 3550;
	}
	 if (TotalTime < 270.f)
	{
		TimeScore = 3700;
	}
	 if (TotalTime < 260.f)
	{
		TimeScore = 3850;
	}
	 if (TotalTime < 250.f)
	{
		TimeScore = 4000;
	}
	 if (TotalTime < 240.f)
	{
		TimeScore = 4150;
	}
	 if (TotalTime < 230.f)
	{
		TimeScore = 4350;
	}
	 if (TotalTime < 220.f)
	{
		TimeScore = 4550;
	}
	 if (TotalTime < 210.f)
	{
		TimeScore = 4750;
	}
	 if (TotalTime < 200.f)
	{
		TimeScore = 5000;
	}
	 if (TotalTime < 190.f)
	{
		TimeScore = 5250;
	}
	 if (TotalTime < 180.f)
	{
		TimeScore = 5550;
	}
	 if (TotalTime < 170.f)
	{
		TimeScore = 5900;
	}
	 if (TotalTime < 160.f)
	{
		TimeScore = 6250;
	}
	 if (TotalTime < 150.f)
	{
		TimeScore = 6650;
	}

}

void ARacingGameGameModeBase::AddToDeathTimer(float input)
{
	DeathTimer += input;
	DeathTimeAdded = "+";
	DeathTimeAdded += FString::FromInt((int)input);
	DeathTimerHUD = true;
	ShowDeathClock = 0.f;
}

void ARacingGameGameModeBase::LoadMainMenuStats()
{
}

void ARacingGameGameModeBase::Reset()
{
	WorldCheckpoint1 = 0.f;
	WorldCheckpoint2 = 0.f;
	WorldCheckpoint3 = 0.f;
	WorldCheckpoint4 = 0.f;
	WorldCheckpoint5 = 0.f;
	WorldCheckpoint6 = 0.f;
	WorldCheckpoint8 = 0.f;
	WorldCheckpoint9 = 0.f;
	WorldCheckpoint10 = 0.f;
	WorldCheckpoint11 = 0.f;
	WorldCheckpoint12 = 0.f;
	WorldCheckpoint13 = 0.f;
	WorldCheckpoint15 = 0.f;
	WorldCheckpoint16 = 0.f;
	WorldCheckpoint17 = 0.f;
	WorldCheckpoint18 = 0.f;
	WorldCheckpoint19 = 0.f;
	WorldCheckpoint20 = 0.f;

	Section1BestTime = 0.f;
	Section2BestTime = 0.f;
	Section3BestTime = 0.f;
	Section4BestTime = 0.f;
	Section5BestTime = 0.f;
	Section6BestTime = 0.f;

	CurrentRound = 1;
	CurrentCheckpoint = 0;

	Section1NewBestTime = false;
	Section2NewBestTime = false;
	Section3NewBestTime = false;
	Section4NewBestTime = false;
	Section5NewBestTime = false;
	Section6NewBestTime = false;
	
	Round1Time = 0.f;
	Round2Time = 0.f;
	Round3Time = 0.f;
	BestRound = 0.f;
	TotalTime = 0.f;
	
	RoundBestTime = 0.f;
	TotalBestTime = 0.f;
	TotalPoints = 0.f;

	BronzeMedal = false;
	SilverMedal = false;
	GoldMedal = false;
	EpicMedal = false;

	TotalPlayerScore = 0;
	TotalBestScore = 0;
	NewBestScore = false;
	TimeScore = 0;
	bGameWon = false;

}

void ARacingGameGameModeBase::LoadMap1()
{
	UGameplayStatics::OpenLevel(GetWorld(), Level1Name);
}

void ARacingGameGameModeBase::LoadMainMenu()
{
	UGameplayStatics::OpenLevel(GetWorld(), MainMenuLevelName);
}

void ARacingGameGameModeBase::SaveGame()
{
	// Getting a RacingSaveGame Instance
	URacingSaveGame* SaveInstance = Cast<URacingSaveGame>(UGameplayStatics::CreateSaveGameObject(URacingSaveGame::StaticClass()));

	if (SaveInstance)
	{
		SaveInstance->StatsShooter.BronzeMedals = MainMenuShooterBronze;
		SaveInstance->StatsShooter.SilverMedals = MainMenuShooterSilver;
		SaveInstance->StatsShooter.GoldMedals = MainMenuShooterGold;
		SaveInstance->StatsShooter.EpicMedals = MainMenuShooterEpic;

		SaveInstance->StatsShooter.BronzeMedals = MainMenuShooterBronze;
		SaveInstance->StatsShooter.SilverMedals = MainMenuShooterSilver;
		SaveInstance->StatsShooter.GoldMedals = MainMenuShooterGold;
		SaveInstance->StatsShooter.EpicMedals = MainMenuShooterEpic;
	}
	if (ShooterMode)
	{
		

		if (SaveInstance)
		{
			SaveInstance->Level1Stats.LevelName = CurrentLevel;



			// Check all sections
		
				
			SaveInstance->Level1Stats.Section1Best = Section1BestTime;
			
			SaveInstance->Level1Stats.Section2Best = Section2BestTime;
		
			SaveInstance->Level1Stats.Section3Best = Section3BestTime;
			
			SaveInstance->Level1Stats.Section4Best = Section4BestTime;
			
			SaveInstance->Level1Stats.Section5Best = Section5BestTime;
			
			SaveInstance->Level1Stats.Section6Best = Section6BestTime;
			
			/*	if (SaveInstance->Level1Stats.Section7Best > Section7BestTime || FMath::IsNearlyZero(SaveInstance->Level1Stats.Section7Best))
				{
					SaveInstance->Level1Stats.Section7Best = Section7BestTime;
				}*/

			// Check all 3 rounds
			float SetBestRound;
			if (BestRound < RoundBestTime || FMath::IsNearlyZero(RoundBestTime))
			{
				NewRoundBest = true;
				SetBestRound = BestRound;
			}
			else
			{
				SetBestRound = RoundBestTime;
			}
			SaveInstance->Level1Stats.RoundBest = SetBestRound;



			// Check Total Time for all 3 rounds
			float SetTotalTime;
			if (TotalTime < TotalBestTime || TotalBestTime == 0.f)
			{
				NewTotalBest = true;
				SetTotalTime = TotalTime;
			}
			else
			{
				SetTotalTime = TotalBestTime;
			}
			SaveInstance->Level1Stats.TotalBest = SetTotalTime;


			SaveInstance->Level1Stats.WorldCheckpoint1Best = WorldCheckpoint1;
			
			SaveInstance->Level1Stats.WorldCheckpoint2Best = WorldCheckpoint2;
			
			SaveInstance->Level1Stats.WorldCheckpoint3Best = WorldCheckpoint3;
			
			SaveInstance->Level1Stats.WorldCheckpoint4Best = WorldCheckpoint4;
			
			SaveInstance->Level1Stats.WorldCheckpoint5Best = WorldCheckpoint5;
			
			SaveInstance->Level1Stats.WorldCheckpoint6Best = WorldCheckpoint6;
			
			//if (SaveInstance->Level1Stats.WorldCheckpoint7Best > WorldCheckpoint7 || FMath::IsNearlyZero(SaveInstance->Level1Stats.WorldCheckpoint7Best))
			//{
			//	SaveInstance->Level1Stats.WorldCheckpoint7Best = WorldCheckpoint7;
			//}
			
			SaveInstance->Level1Stats.WorldCheckpoint8Best = WorldCheckpoint8;
			
			SaveInstance->Level1Stats.WorldCheckpoint9Best = WorldCheckpoint9;
			
			SaveInstance->Level1Stats.WorldCheckpoint10Best = WorldCheckpoint10;
			
			SaveInstance->Level1Stats.WorldCheckpoint11Best = WorldCheckpoint11;
			
			SaveInstance->Level1Stats.WorldCheckpoint12Best = WorldCheckpoint12;
			
			SaveInstance->Level1Stats.WorldCheckpoint13Best = WorldCheckpoint13;
			
			//if (SaveInstance->Level1Stats.WorldCheckpoint14Best > WorldCheckpoint14 || FMath::IsNearlyZero(SaveInstance->Level1Stats.WorldCheckpoint14Best))
			//{
			//	SaveInstance->Level1Stats.WorldCheckpoint14Best = WorldCheckpoint14;
			//}
		
			SaveInstance->Level1Stats.WorldCheckpoint15Best = WorldCheckpoint15;
			
			SaveInstance->Level1Stats.WorldCheckpoint16Best = WorldCheckpoint16;
		
			SaveInstance->Level1Stats.WorldCheckpoint17Best = WorldCheckpoint17;
		
			SaveInstance->Level1Stats.WorldCheckpoint18Best = WorldCheckpoint18;
			
			SaveInstance->Level1Stats.WorldCheckpoint19Best = WorldCheckpoint19;
			
			SaveInstance->Level1Stats.WorldCheckpoint20Best = WorldCheckpoint20;
			
			//if (SaveInstance->Level1Stats.WorldCheckpoint21Best > WorldCheckpoint21 || FMath::IsNearlyZero(SaveInstance->Level1Stats.WorldCheckpoint21Best))
			//{
			//	SaveInstance->Level1Stats.WorldCheckpoint21Best = WorldCheckpoint21;
			//}

			float SetBestScore;
			if (TotalBestScore < TotalPlayerScore)
			{
				NewBestScore = true;
				SetBestScore = TotalBestScore;
			}
			else
			{
				SetBestScore = TotalPlayerScore;
			}
			SaveInstance->Level1Stats.BestPoints = SetBestScore;

			SaveInstance->TimeAttack = TimeAttack;
			SaveInstance->ShooterMode = ShooterMode;

			// Save Game to slot
			UGameplayStatics::SaveGameToSlot(SaveInstance, TEXT("Player1"), 1);
		}

		

	}
	else if (TimeAttack)
	{
	// Getting a RacingSaveGame Instance
	

		if (SaveInstance)
		{
			SaveInstance->Level1StatsTimeAttack.LevelName = CurrentLevel;



		


			SaveInstance->Level1StatsTimeAttack.Section1Best = Section1BestTime;

			SaveInstance->Level1StatsTimeAttack.Section2Best = Section2BestTime;

			SaveInstance->Level1StatsTimeAttack.Section3Best = Section3BestTime;

			SaveInstance->Level1StatsTimeAttack.Section4Best = Section4BestTime;

			SaveInstance->Level1StatsTimeAttack.Section5Best = Section5BestTime;

			SaveInstance->Level1StatsTimeAttack.Section6Best = Section6BestTime;

			//SaveInstance->Level1Stats.Section7Best = Section7BestTime;
			

				


			
			float SetBestRound;
			if (BestRound < RoundBestTime || FMath::IsNearlyZero(RoundBestTime))
			{
				NewRoundBest = true;
				SetBestRound = BestRound;
			}
			else
			{
				SetBestRound = RoundBestTime;
			}
			SaveInstance->Level1StatsTimeAttack.RoundBest = SetBestRound;



			// Check Total Time 
			float SetTotalTime;
			if (TotalTime < TotalBestTime || TotalBestTime == 0.f)
			{
				NewTotalBest = true;
				SetTotalTime = TotalTime;
			}
			else
			{
				SetTotalTime = TotalBestTime;
			}
			SaveInstance->Level1StatsTimeAttack.TotalBest = SetTotalTime;


			SaveInstance->Level1StatsTimeAttack.WorldCheckpoint1Best = WorldCheckpoint1;

			SaveInstance->Level1StatsTimeAttack.WorldCheckpoint2Best = WorldCheckpoint2;

			SaveInstance->Level1StatsTimeAttack.WorldCheckpoint3Best = WorldCheckpoint3;

			SaveInstance->Level1StatsTimeAttack.WorldCheckpoint4Best = WorldCheckpoint4;

			SaveInstance->Level1StatsTimeAttack.WorldCheckpoint5Best = WorldCheckpoint5;

			SaveInstance->Level1StatsTimeAttack.WorldCheckpoint6Best = WorldCheckpoint6;

			//if (SaveInstance->Level1Stats.WorldCheckpoint7Best > WorldCheckpoint7 || FMath::IsNearlyZero(SaveInstance->Level1Stats.WorldCheckpoint7Best))
			//{
			//	SaveInstance->Level1Stats.WorldCheckpoint7Best = WorldCheckpoint7;
			//}

			SaveInstance->Level1StatsTimeAttack.WorldCheckpoint8Best = WorldCheckpoint8;

			SaveInstance->Level1StatsTimeAttack.WorldCheckpoint9Best = WorldCheckpoint9;

			SaveInstance->Level1StatsTimeAttack.WorldCheckpoint10Best = WorldCheckpoint10;

			SaveInstance->Level1StatsTimeAttack.WorldCheckpoint11Best = WorldCheckpoint11;

			SaveInstance->Level1StatsTimeAttack.WorldCheckpoint12Best = WorldCheckpoint12;

			SaveInstance->Level1StatsTimeAttack.WorldCheckpoint13Best = WorldCheckpoint13;

			//if (SaveInstance->Level1Stats.WorldCheckpoint14Best > WorldCheckpoint14 || FMath::IsNearlyZero(SaveInstance->Level1Stats.WorldCheckpoint14Best))
			//{
			//	SaveInstance->Level1Stats.WorldCheckpoint14Best = WorldCheckpoint14;
			//}

			SaveInstance->Level1StatsTimeAttack.WorldCheckpoint15Best = WorldCheckpoint15;

			SaveInstance->Level1StatsTimeAttack.WorldCheckpoint16Best = WorldCheckpoint16;

			SaveInstance->Level1StatsTimeAttack.WorldCheckpoint17Best = WorldCheckpoint17;

			SaveInstance->Level1StatsTimeAttack.WorldCheckpoint18Best = WorldCheckpoint18;

			SaveInstance->Level1StatsTimeAttack.WorldCheckpoint19Best = WorldCheckpoint19;

			SaveInstance->Level1StatsTimeAttack.WorldCheckpoint20Best = WorldCheckpoint20;

			//if (SaveInstance->Level1Stats.WorldCheckpoint21Best > WorldCheckpoint21 || FMath::IsNearlyZero(SaveInstance->Level1Stats.WorldCheckpoint21Best))
			//{
			//	SaveInstance->Level1Stats.WorldCheckpoint21Best = WorldCheckpoint21;
			//}

			float SetBestScore;
			if (TotalPlayerScore < TotalBestScore)
			{
				NewBestScore = true;
				SetBestScore = TotalPlayerScore;
			}
			else
			{
				SetBestScore = TotalBestScore;
			}
			SaveInstance->Level1StatsTimeAttack.BestPoints = SetBestScore;

			SaveInstance->TimeAttack = TimeAttack;
			SaveInstance->ShooterMode = ShooterMode;

			// Save Game to slot
			UGameplayStatics::SaveGameToSlot(SaveInstance, TEXT("Player1"), 1);
		}


	}
	
	
	

	
	
	
}

void ARacingGameGameModeBase::LoadGame()
{

	// Getting a RacingSaveGame Instance
	URacingSaveGame* LoadInstance = Cast<URacingSaveGame>(UGameplayStatics::CreateSaveGameObject(URacingSaveGame::StaticClass()));

	LoadInstance = Cast<URacingSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Player1"),1));

	
	if (LoadInstance)
	{
		GameLoaded = true;
		ShooterMode = LoadInstance->ShooterMode;
		TimeAttack = LoadInstance->TimeAttack;

		MainMenuShooterBronze = LoadInstance->StatsShooter.BronzeMedals;
		MainMenuShooterSilver = LoadInstance->StatsShooter.SilverMedals;
		MainMenuShooterGold = LoadInstance->StatsShooter.GoldMedals;
		MainMenuShooterEpic = LoadInstance->StatsShooter.EpicMedals;

		MainMenuShooterBronze = LoadInstance->StatsShooter.BronzeMedals;
		MainMenuShooterSilver = LoadInstance->StatsShooter.SilverMedals;
		MainMenuShooterGold = LoadInstance->StatsShooter.GoldMedals;
		MainMenuShooterEpic = LoadInstance->StatsShooter.EpicMedals;

	}


	
	if (ShooterMode)
	{
		

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
			WorldCheckpoint11 = LoadInstance->Level1Stats.WorldCheckpoint11Best;
			WorldCheckpoint12 = LoadInstance->Level1Stats.WorldCheckpoint12Best;
			WorldCheckpoint13 = LoadInstance->Level1Stats.WorldCheckpoint13Best;
			/*WorldCheckpoint14= LoadInstance->Level1Stats.WorldCheckpoint14Best;*/
			WorldCheckpoint15 = LoadInstance->Level1Stats.WorldCheckpoint15Best;
			WorldCheckpoint16 = LoadInstance->Level1Stats.WorldCheckpoint16Best;
			WorldCheckpoint17 = LoadInstance->Level1Stats.WorldCheckpoint17Best;
			WorldCheckpoint18 = LoadInstance->Level1Stats.WorldCheckpoint18Best;
			WorldCheckpoint19 = LoadInstance->Level1Stats.WorldCheckpoint19Best;
			WorldCheckpoint20 = LoadInstance->Level1Stats.WorldCheckpoint20Best;
			/*WorldCheckpoint21= LoadInstance->Level1Stats.WorldCheckpoint21Best;*/

			RoundBestTime = LoadInstance->Level1Stats.RoundBest;
			TotalBestTime = LoadInstance->Level1Stats.TotalBest;
		
			TotalBestScore = LoadInstance->Level1Stats.BestPoints;

			CurrentLevel = LoadInstance->Level1Stats.LevelName;


			
		}
		if (Section1BestTime == 0.f)
		{
			GameLoaded = false;
		}

	}
	else if (TimeAttack)
	{
		

		if (LoadInstance)
		{
			Section1BestTime = LoadInstance->Level1StatsTimeAttack.Section1Best;
			Section2BestTime = LoadInstance->Level1StatsTimeAttack.Section2Best;
			Section3BestTime = LoadInstance->Level1StatsTimeAttack.Section3Best;
			Section4BestTime = LoadInstance->Level1StatsTimeAttack.Section4Best;
			Section5BestTime = LoadInstance->Level1StatsTimeAttack.Section5Best;
			Section6BestTime = LoadInstance->Level1StatsTimeAttack.Section6Best;
			/*	Section7BestTime = LoadInstance->Level1Stats.Section7Best;*/

			WorldCheckpoint1 = LoadInstance->Level1StatsTimeAttack.WorldCheckpoint1Best;
			WorldCheckpoint2 = LoadInstance->Level1StatsTimeAttack.WorldCheckpoint2Best;
			WorldCheckpoint3 = LoadInstance->Level1StatsTimeAttack.WorldCheckpoint3Best;
			WorldCheckpoint4 = LoadInstance->Level1StatsTimeAttack.WorldCheckpoint4Best;
			WorldCheckpoint5 = LoadInstance->Level1StatsTimeAttack.WorldCheckpoint5Best;
			WorldCheckpoint6 = LoadInstance->Level1StatsTimeAttack.WorldCheckpoint6Best;
			/*WorldCheckpoint7 = LoadInstance->Level1Stats.WorldCheckpoint7Best;*/
			WorldCheckpoint8 = LoadInstance->Level1StatsTimeAttack.WorldCheckpoint8Best;
			WorldCheckpoint9 = LoadInstance->Level1StatsTimeAttack.WorldCheckpoint9Best;
			WorldCheckpoint10 = LoadInstance->Level1StatsTimeAttack.WorldCheckpoint10Best;
			WorldCheckpoint11 = LoadInstance->Level1StatsTimeAttack.WorldCheckpoint11Best;
			WorldCheckpoint12 = LoadInstance->Level1StatsTimeAttack.WorldCheckpoint12Best;
			WorldCheckpoint13 = LoadInstance->Level1StatsTimeAttack.WorldCheckpoint13Best;
			/*WorldCheckpoint14= LoadInstance->Level1Stats.WorldCheckpoint14Best;*/
			WorldCheckpoint15 = LoadInstance->Level1StatsTimeAttack.WorldCheckpoint15Best;
			WorldCheckpoint16 = LoadInstance->Level1StatsTimeAttack.WorldCheckpoint16Best;
			WorldCheckpoint17 = LoadInstance->Level1StatsTimeAttack.WorldCheckpoint17Best;
			WorldCheckpoint18 = LoadInstance->Level1StatsTimeAttack.WorldCheckpoint18Best;
			WorldCheckpoint19 = LoadInstance->Level1StatsTimeAttack.WorldCheckpoint19Best;
			WorldCheckpoint20 = LoadInstance->Level1StatsTimeAttack.WorldCheckpoint20Best;
			/*WorldCheckpoint21= LoadInstance->Level1Stats.WorldCheckpoint21Best;*/

			RoundBestTime = LoadInstance->Level1StatsTimeAttack.RoundBest;
			TotalBestTime = LoadInstance->Level1StatsTimeAttack.TotalBest;

			TotalBestScore = LoadInstance->Level1StatsTimeAttack.BestPoints;

			CurrentLevel = LoadInstance->Level1StatsTimeAttack.LevelName;

			
		}
		if (Section1BestTime == 0.f)
		{
			GameLoaded = false;
		}
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

		tempSpeedBoost = World->SpawnActor<ASpeedBoosterv1>(SpeedboostBP, SpeedBoost11Vector, SpeedBoost11Rotator);
		SpeedBoostArray.Add(tempSpeedBoost);
		SpeedBoostArray[10]->SetActorHiddenInGame(false);
		SpeedBoostArray[10]->SetActorEnableCollision(true);

		tempSpeedBoost = World->SpawnActor<ASpeedBoosterv1>(SpeedboostBP, SpeedBoost12Vector, SpeedBoost12Rotator);
		SpeedBoostArray.Add(tempSpeedBoost);
		SpeedBoostArray[11]->SetActorHiddenInGame(false);
		SpeedBoostArray[11]->SetActorEnableCollision(true);




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

		tempTarget = World->SpawnActor<ATarget>(TargetBP, Target15Vector, Target15Rotator);
		TargetArray.Add(tempTarget);
		TargetArray[14]->SetActorHiddenInGame(false);
		TargetArray[14]->SetActorEnableCollision(true);

		tempTarget = World->SpawnActor<ATarget>(TargetBP, Target16Vector, Target16Rotator);
		TargetArray.Add(tempTarget);
		TargetArray[15]->SetActorHiddenInGame(false);
		TargetArray[15]->SetActorEnableCollision(true);

		tempTarget = World->SpawnActor<ATarget>(TargetBP, Target17Vector, Target17Rotator);
		TargetArray.Add(tempTarget);
		TargetArray[16]->SetActorHiddenInGame(false);
		TargetArray[16]->SetActorEnableCollision(true);

		tempTarget = World->SpawnActor<ATarget>(TargetBP, Target18Vector, Target18Rotator);
		TargetArray.Add(tempTarget);
		TargetArray[17]->SetActorHiddenInGame(false);
		TargetArray[17]->SetActorEnableCollision(true);

		tempTarget = World->SpawnActor<ATarget>(TargetBP, Target19Vector, Target19Rotator);
		TargetArray.Add(tempTarget);
		TargetArray[18]->SetActorHiddenInGame(false);
		TargetArray[18]->SetActorEnableCollision(true);

		tempTarget = World->SpawnActor<ATarget>(TargetBP, Target20Vector, Target20Rotator);
		TargetArray.Add(tempTarget);
		TargetArray[19]->SetActorHiddenInGame(false);
		TargetArray[19]->SetActorEnableCollision(true);

		tempTarget = World->SpawnActor<ATarget>(TargetBP, Target21Vector, Target21Rotator);
		TargetArray.Add(tempTarget);
		TargetArray[20]->SetActorHiddenInGame(false);
		TargetArray[20]->SetActorEnableCollision(true);
		
	}

}

void ARacingGameGameModeBase::RespawnItems()
{
	if (SpeedBoostArray.Num() > 0)
	{
		for (int i{}; i < SpeedBoostArray.Num(); i++)
		{
			if (SpeedBoostArray[i]->isHit)
			{
				SpeedBoostArray[i]->bMagnetPull = false;
				SpeedBoostArray[i]->SetActorLocation(SpeedBoostArray[i]->StartLocation);
				SpeedBoostArray[i]->SetActorRotation(SpeedBoostArray[i]->StartRotation);
				SpeedBoostArray[i]->SetActorHiddenInGame(false);
				SpeedBoostArray[i]->SetActorEnableCollision(true);
				SpeedBoostArray[i]->isHit = false;
			}
		}
	}
	if (TargetArray.Num() > 0)
	{
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
}


