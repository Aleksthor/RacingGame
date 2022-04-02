// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RacingGameGameModeBase.generated.h"

/**
 * 
 */

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

	TArray<class ACheckpointCollider*> CheckpointArray;
	ACheckpointCollider* tempCheckpoint;

	UPROPERTY(EditAnywhere, Category = "GameModeVariable")
	TSubclassOf<class ATarget> TargetBP;

	TArray<class ATarget*> TargetArray;
	ATarget* tempTarget;

	UPROPERTY(EditAnywhere, Category = "GameModeVariable")
	TSubclassOf<class ASpeedBoosterv1> SpeedboostBP;

	TArray<class ASpeedBoosterv1*> SpeedBoostArray;
	ASpeedBoosterv1* tempSpeedBoost;

	

	

	class APlayerCar* Player{ nullptr };

	/** Default Values */

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
	int CurrentRound = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameModeVariable")
	int CurrentCheckpoint = 0;


	FString CurrentLevel;

	FString Level1 = "MOSSYMOOR";

	FName Level1Name = "MOSSYMOOR";

	/** Tick Functions */

	void CurrentRoundFunction();


	/** Checkpoint Variables*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
	int TotalCheckpoints = 6;

	// Positions and Rotations

	// Checkpoints
	FVector Checkpoint1Vector = FVector(30700.f, 5700.f, 22750.f);
	FRotator Checkpoint1Rotator = FRotator(0.f,-60.f,0.f);

	FVector Checkpoint2Vector = FVector(5900.f,-6600.f,13000.f);
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

	FVector SpeedBoost1Vector = FVector(-14150.f, 14350.f, 22650.f);
	FRotator SpeedBoost1Rotator = FRotator(0.f, -150.f, 0.f);

	FVector SpeedBoost2Vector = FVector(8550.f, 6000.f, 24200.f);
	FRotator SpeedBoost2Rotator = FRotator(0.f, 170.f, 0.f);

	FVector SpeedBoost3Vector = FVector(27000.f, 2080.f, 23170.f);
	FRotator SpeedBoost3Rotator = FRotator(0.f, -190.f, 0.f);

	FVector SpeedBoost4Vector = FVector(22350.f, -1440.f, 15310.f);
	FRotator SpeedBoost4Rotator = FRotator(0.f, -80.f, 0.f);

	FVector SpeedBoost5Vector = FVector(-5350.f, -7350.f, 12130.f);
	FRotator SpeedBoost5Rotator = FRotator(0.f, 40.f, 0.f);

	FVector SpeedBoost6Vector = FVector(15410.f, -26260.f, 5540.f);
	FRotator SpeedBoost6Rotator = FRotator(0.f, -90.f, 0.f);

	FVector SpeedBoost7Vector = FVector(23690.f, -34370.f, 4380.f);
	FRotator SpeedBoost7Rotator = FRotator(0.f, -190.f, 0.f);

	FVector SpeedBoost8Vector = FVector(30460.f, -16640.f,8050.f);
	FRotator SpeedBoost8Rotator = FRotator(0.f, 0.f, 0.f);

	FVector SpeedBoost9Vector = FVector(32940.f, -12470.f, 11220.f);
	FRotator SpeedBoost9Rotator = FRotator(0.f, 0.f, 0.f);

	FVector SpeedBoost10Vector = FVector(10580.f, 9250.f, 20530.f);
	FRotator SpeedBoost10Rotator = FRotator(0.f, 70.f, 0.f);


	// Targets

	FVector Target1Vector = FVector(30800.f, -5950.f, 17660.f);
	FRotator Target1Rotator = FRotator(0.f, 50.f, 0.f);

	FVector Target2Vector = FVector(37110.f, -530.f, 19910.f);
	FRotator Target2Rotator = FRotator(0.f, 120.f, 0.f);

	FVector Target3Vector = FVector(33280.f, 7770.f, 22190.f);
	FRotator Target3Rotator = FRotator(0.f, -140.f, 0.f);

	FVector Target4Vector = FVector(44690.f, -27970.f, 5940.f);
	FRotator Target4Rotator = FRotator(0.f, 160.f, 0.f);

	FVector Target5Vector = FVector(45840.f, -27500.f, 5970.f);
	FRotator Target5Rotator = FRotator(0.f, 170.f, 0.f);

	FVector Target6Vector = FVector(46660.f, -26830.f, 6060.f);
	FRotator Target6Rotator = FRotator(0.f, 190.f, 0.f);

	FVector Target7Vector = FVector(35550.f, -13600.f, 11850.f);
	FRotator Target7Rotator = FRotator(0.f, 0.f, 0.f);

	FVector Target8Vector = FVector(43250.f, 4420.f, 13950.f);
	FRotator Target8Rotator = FRotator(0.f, -120.f, 0.f);

	FVector Target9Vector = FVector(32070.f, 14190.f, 14960.f);
	FRotator Target9Rotator = FRotator(0.f, -70.f, 0.f);

	FVector Target10Vector = FVector(-15700.f, 14060.f, 22710.f);
	FRotator Target10Rotator = FRotator(0.f, -70.f, 0.f);

	FVector Target11Vector = FVector(-6950.f, 10310.f, 24510.f);
	FRotator Target11Rotator = FRotator(0.f, 110.f, 0.f);

	FVector Target12Vector = FVector(34950.f, -13050.f, 12070.f);
	FRotator Target12Rotator = FRotator(0.f, 0.f, 0.f);

	FVector Target13Vector = FVector(6220.f, 2660.f, 21680.f);
	FRotator Target13Rotator = FRotator(0.f, 0.f, 0.f);

	FVector Target14Vector = FVector(3090.f, 150.f, 21990.f);
	FRotator Target14Rotator = FRotator(0.f, 0.f, 0.f);

	FVector Target15Vector = FVector(7980.f, 10260.f, 25100.f);
	FRotator Target15Rotator = FRotator(0.f, 0.f, 0.f);

	FVector Target16Vector = FVector(20310.f, 3490.f, 15870.f);
	FRotator Target16Rotator = FRotator(0.f, 0.f, 0.f);

	FVector Target17Vector = FVector(9860.f, -39660.f, 5720.f);
	FRotator Target17Rotator = FRotator(0.f, 0.f, 0.f);

	FVector Target18Vector = FVector(8000.f, -5380.f, 13470.f);
	FRotator Target18Rotator = FRotator(0.f, 0.f, 0.f);

	FVector Target19Vector = FVector(11600.f, -17580.f, 9010.f);
	FRotator Target19Rotator = FRotator(0.f, 0.f, 0.f);

	/** Save Data */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameModeVariable")
	bool Saved = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameModeVariable")
	FString PlayerName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
	float Section1BestTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
	float Section2BestTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
	float Section3BestTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
	float Section4BestTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
	float Section5BestTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
	float Section6BestTime;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
	//float Section7BestTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
	float Round1Time;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
	float Round2Time;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
	float Round3Time;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
	float TotalTime;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
	float RoundBestTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
	float TotalBestTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
	int TotalPoints;




	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
		float WorldCheckpoint1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
		float WorldCheckpoint2;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
		float WorldCheckpoint3;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
		float WorldCheckpoint4;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
		float WorldCheckpoint5;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
		float WorldCheckpoint6;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
	//	float WorldCheckpoint7;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
		float WorldCheckpoint8;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
		float WorldCheckpoint9;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
		float WorldCheckpoint10;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
		float WorldCheckpoint11;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
		float WorldCheckpoint12;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
		float WorldCheckpoint13;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
	//	float WorldCheckpoint14;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
		float WorldCheckpoint15;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
		float WorldCheckpoint16;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
		float WorldCheckpoint17;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
		float WorldCheckpoint18;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
		float WorldCheckpoint19;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
		float WorldCheckpoint20;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
	//	float WorldCheckpoint21;

	/** Functions */

	UFUNCTION()
	void GameWon();

	UFUNCTION()
	void Reset();

	UFUNCTION(BlueprintCallable)
	void LoadMap1();

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


	/** Used for countdown before start */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameModeVariable")
	int SecondsUntilStart = 3;

	float OneSecond = 1.f;
	float PreGameClock = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameModeVariable")
	bool RacingMode = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameModeVariable")
	bool ShooterMode = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
	int TotalPlayerScore;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
	int TimeScore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameModeVariable")
	bool bGameWon = false;
};
