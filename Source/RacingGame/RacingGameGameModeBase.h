// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RacingGameGameModeBase.generated.h"

/**
 * 
 */
class USoundCue;

// Code that is commented out is there to be able to implement again if we want it
UCLASS()
class RACINGGAME_API ARacingGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	ARacingGameGameModeBase();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	/** Classes to Spawn */

	UPROPERTY(EditAnywhere, Category = "GameModeVariable")
	TSubclassOf<class ACheckpointCollider> CheckpointColliderBP;

	UPROPERTY(EditAnywhere, Category = "GameModeVariable")
	TSubclassOf<class ATarget> TargetBP;

	UPROPERTY(EditAnywhere, Category = "GameModeVariable")
	TSubclassOf<class ASpeedBoosterv1> SpeedboostBP;

	UPROPERTY(EditAnywhere, Category = "GameModeVariable")
	TSubclassOf<class ARacingEnemy> GhostBP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameModeVariable")
	ARacingEnemy* SpawnedGhost;

	TArray<class ACheckpointCollider*> CheckpointArray;
	ACheckpointCollider* tempCheckpoint;

	TArray<class ATarget*> TargetArray;
	ATarget* tempTarget;

	TArray<class ASpeedBoosterv1*> SpeedBoostArray;
	ASpeedBoosterv1* tempSpeedBoost;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameModeVariable")
	USoundCue* GameWonSound{ nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameModeVariable")
	USoundCue* GameWonGoldSound{ nullptr };

	
	class APlayerCar* Player{ nullptr };

	/** Default Values */

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
	int CurrentRound = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameModeVariable")
	int CurrentCheckpoint = 0;


	FString CurrentLevel;

	FString Level1 = "MOSSYMOOR";

	FName Level1Name = "MOSSYMOOR";
	FName MainMenuLevelName = "MainMenuLevel";


	/** Tick Functions */

	void CurrentRoundFunction();



	/** Ghost Data */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FVector> LocationArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FRotator> RotationArray;

	float SaveGhostDataTimer = 0.016;

	float SaveGhostDataClock = 0.f;

	float LoadGhostDataTimer = 0.016;

	float LoadGhostDataClock = 0.f;

	int CurrentFrame = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ShowGhost;


	/** Checkpoint Variables*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
	int TotalCheckpoints = 6;

	// Positions and Rotations

	// Checkpoints
	FVector Checkpoint1Vector = FVector(30700.f, 5700.f, 22750.f);
	FRotator Checkpoint1Rotator = FRotator(0.f,-60.f,0.f);

	FVector Checkpoint2Vector = FVector(9750.f,-7000.f,13200.f);
	FRotator Checkpoint2Rotator = FRotator(0.f,90.f,0.f);

	FVector Checkpoint3Vector = FVector(44800.f,-23500.f,5950.f);
	FRotator Checkpoint3Rotator = FRotator(0.f,-20.f,0.f);

	FVector Checkpoint4Vector = FVector(40340.f,-8440.f,13550.f);
	FRotator Checkpoint4Rotator = FRotator(0.f,-30.f,0.f);

	FVector Checkpoint5Vector = FVector(26100.f,12790.f,16100.f);
	FRotator Checkpoint5Rotator = FRotator(0.f,-90.f,0.f);

	FVector Checkpoint6Vector = FVector(-14850.f,7550.f,22500.f);
	FRotator Checkpoint6Rotator = FRotator(0.f,20.f,0.f);

	/*FVector Checkpoint7Vector = FVector(-14850.f, 7550.f, 22500.f);
	FRotator Checkpoint7Rotator = FRotator(0.f, 20.f, 0.f);*/

	// SpeedBoosters

	FVector SpeedBoost1Vector = FVector(-10170.f, 13630.f, 23530.f);
	FRotator SpeedBoost1Rotator = FRotator(0.f, -200.f, 0.f);

	FVector SpeedBoost2Vector = FVector(13730.f, 4980.f, 23170.f);
	FRotator SpeedBoost2Rotator = FRotator(0.f, -200.f, 0.f);

	FVector SpeedBoost3Vector = FVector(-5900.f, -7810.f, 12120.f);
	FRotator SpeedBoost3Rotator = FRotator(0.f, 50.f, 0.f);

	FVector SpeedBoost4Vector = FVector(15480.f, -26230.f, 5530.f);
	FRotator SpeedBoost4Rotator = FRotator(0.f, -110.f, 0.f);

	FVector SpeedBoost5Vector = FVector(28760.f, -31960.f, 4030.f);
	FRotator SpeedBoost5Rotator = FRotator(0.f, -150.f, 0.f);

	FVector SpeedBoost6Vector = FVector(37210.f, -17800.f, 7100.f);
	FRotator SpeedBoost6Rotator = FRotator(0.f, 0.f, 0.f);

	FVector SpeedBoost7Vector = FVector(33790.f, -12470.f, 11280.f);
	FRotator SpeedBoost7Rotator = FRotator(0.f, -170.f, 0.f);

	FVector SpeedBoost8Vector = FVector(29770.f, 12520.f,14980.f);
	FRotator SpeedBoost8Rotator = FRotator(0.f, 0.f, 0.f);

	FVector SpeedBoost9Vector = FVector(1590.f, 980.f, 21580.f); 
	FRotator SpeedBoost9Rotator = FRotator(0.f, 0.f, 0.f);

	FVector SpeedBoost10Vector = FVector(13570.f, 6300.f, 13100.f);
	FRotator SpeedBoost10Rotator = FRotator(0.f, 0.f, 0.f);

	FVector SpeedBoost11Vector = FVector(4950.f, -25300.f, 7030.f);
	FRotator SpeedBoost11Rotator = FRotator(0.f, 0.f, 0.f);

	FVector SpeedBoost12Vector = FVector(19750.f, -11960.f, 10480.f);
	FRotator SpeedBoost12Rotator = FRotator(0.f, 0.f, 0.f);




	// Targets

	FVector Target1Vector = FVector(-15740.f, 14170.f, 22690.f);
	FRotator Target1Rotator = FRotator(0.f, 0.f, 0.f);

	FVector Target2Vector = FVector(8040.f, 8070.f, 23340.f);
	FRotator Target2Rotator = FRotator(0.f, 0.f, 0.f);

	FVector Target3Vector = FVector(35380.f, 6350.f, 22270.f); 
	FRotator Target3Rotator = FRotator(0.f, 0.f, 0.f);

	FVector Target4Vector = FVector(31280.f, -5620.f, 17940.f);
	FRotator Target4Rotator = FRotator(0.f, 0.f, 0.f);

	FVector Target5Vector = FVector(18490.f, 1050.f, 15810.f);
	FRotator Target5Rotator = FRotator(0.f, 0.f, 0.f);

	FVector Target6Vector = FVector(17190.f, -6170.f, 16500.f);
	FRotator Target6Rotator = FRotator(0.f, 0.f, 0.f);

	FVector Target7Vector = FVector(17980.f, 3120.f, 24210.f);
	FRotator Target7Rotator = FRotator(0.f, 0.f, 0.f);

	FVector Target8Vector = FVector(4410.f, -17390.f, 10900.f);
	FRotator Target8Rotator = FRotator(0.f, 0.f, 0.f);

	FVector Target9Vector = FVector(12640.f, -16670.f, 8430.f);
	FRotator Target9Rotator = FRotator(0.f, 0.f, 0.f);

	FVector Target10Vector = FVector(18470.f, -20480.f, 6870.f);
	FRotator Target10Rotator = FRotator(0.f, 0.f, 0.f);

	FVector Target11Vector = FVector(19500.f, -34350.f, 5940.f);
	FRotator Target11Rotator = FRotator(0.f, 0.f, 0.f);

	FVector Target12Vector = FVector(34950.f, -13050.f, 12070.f);
	FRotator Target12Rotator = FRotator(0.f, 0.f, 0.f);

	FVector Target13Vector = FVector(44660.f, -28100.f, 6160.f);
	FRotator Target13Rotator = FRotator(0.f, 0.f, 0.f);

	FVector Target14Vector = FVector(45470.f, -27150.f, 6200.f);
	FRotator Target14Rotator = FRotator(0.f, 0.f, 0.f);

	FVector Target15Vector = FVector(46350.f, -26090.f, 6240.f);
	FRotator Target15Rotator = FRotator(0.f, 0.f, 0.f);

	FVector Target16Vector = FVector(35780.f, -13650.f, 11930.f);
	FRotator Target16Rotator = FRotator(0.f, 0.f, 0.f);

	FVector Target17Vector = FVector(40720.f, -5260.f, 14530.f);
	FRotator Target17Rotator = FRotator(0.f, 0.f, 0.f);

	FVector Target18Vector = FVector(31970.f, 14230.f, 15260.f);
	FRotator Target18Rotator = FRotator(0.f, 0.f, 0.f);

	FVector Target19Vector = FVector(-2040.f, 890.f, 22480.f);
	FRotator Target19Rotator = FRotator(0.f, 0.f, 0.f);

	FVector Target20Vector = FVector(-1500.f, -7540.f, 13180.f);
	FRotator Target20Rotator = FRotator(0.f, 0.f, 0.f);

	FVector Target21Vector = FVector(37610.f, -40480.f, 7050.f);
	FRotator Target21Rotator = FRotator(0.f, 0.f, 0.f);



	/** Save Data */

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	TArray<FVector> GhostLocationArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	TArray<FRotator> GhostRotationArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	bool Saved = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	bool GameLoaded = false;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	float CurrentSectionBest;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	float Section1BestTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	float Section2BestTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	float Section3BestTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	float Section4BestTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	float Section5BestTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	float Section6BestTime;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	bool Section1NewBestTime = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	bool Section2NewBestTime = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	bool Section3NewBestTime = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	bool Section4NewBestTime = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	bool Section5NewBestTime = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	bool Section6NewBestTime = false;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
	//float Section7BestTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	float Round1Time;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	float Round2Time;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	float Round3Time;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	float BestRound;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	float TotalTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	float RoundBestTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	float TotalBestTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	int TotalPoints;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	bool BronzeMedal = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	bool SilverMedal = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	bool GoldMedal = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	bool EpicMedal = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	bool NewRoundBest = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	bool NewTotalBest = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	FString HUDMedalString{""};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	float WorldCheckpoint1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	float WorldCheckpoint2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	float WorldCheckpoint3;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	float WorldCheckpoint4;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	float WorldCheckpoint5;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	float WorldCheckpoint6;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
	//	float WorldCheckpoint7;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	float WorldCheckpoint8;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	float WorldCheckpoint9;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	float WorldCheckpoint10;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	float WorldCheckpoint11;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	float WorldCheckpoint12;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	float WorldCheckpoint13;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
	//	float WorldCheckpoint14;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	float WorldCheckpoint15;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	float WorldCheckpoint16;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	float WorldCheckpoint17;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	float WorldCheckpoint18;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	float WorldCheckpoint19;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	float WorldCheckpoint20;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
	//	float WorldCheckpoint21;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	int MainMenuShooterBronze;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	int MainMenuShooterSilver;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	int MainMenuShooterGold;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	int MainMenuShooterEpic;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	int MainMenuTimeAttackBronze;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	int MainMenuTimeAttackSilver;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	int MainMenuTimeAttackGold;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	int MainMenuTimeAttackEpic;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	float NextBest;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	float DeathTimer = 20.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	FString DeathTimeAdded;


	bool DeathTimerHUD = false;

	float ShowDeathTimer = 2.f;

	float ShowDeathClock = 0.f;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable | SaveData")
	int NoHitRun;

	/** Functions */

	UFUNCTION()
	void GameWon();

	UFUNCTION()
	void GameLost();

	UFUNCTION(BlueprintCallable)
	void Reset();

	UFUNCTION(BlueprintCallable)
	void LoadMap1();

	UFUNCTION(BlueprintCallable)
	void LoadMainMenu();

	UFUNCTION(BlueprintCallable)
	void SaveGame();

	UFUNCTION(BlueprintCallable)
	void LoadGame();
	
	UFUNCTION()
	void InitItems();

	UFUNCTION()
	void RespawnItems();

	UFUNCTION()
	void SwitchTimer();

	UFUNCTION()
	void AddToDeathTimer(float input);

	UFUNCTION()
	void LoadMainMenuStats();


	/** Used for countdown before start */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameModeVariable")
	int SecondsUntilStart = 3;

	float OneSecond = 1.f;
	float PreGameClock = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameModeVariable")
	bool TimeAttack = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameModeVariable")
	bool ShooterMode = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
	int TotalPlayerScore;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
	int TotalBestScore;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
	bool NewBestScore = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
	int TimeScore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameModeVariable")
	bool bGameWon = false;
};
