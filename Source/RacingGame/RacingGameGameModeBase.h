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

	FVector SpeedBoost10Vector = FVector(39460.f, -10770.f, 13960.f);
	FRotator SpeedBoost10Rotator = FRotator(0.f, -40.f, 0.f);

	FVector SpeedBoost11Vector = FVector(10580.f, 9250.f, 20530.f);
	FRotator SpeedBoost11Rotator = FRotator(0.f, 70.f, 0.f);

	/** Save Data */

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

	


	/** Used for countdown before start */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameModeVariable")
	int SecondsUntilStart = 3;

	float OneSecond = 1.f;
	float PreGameClock = 0.f;




};
