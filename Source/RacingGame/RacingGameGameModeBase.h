// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RacingGameGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class RACINGGAME_API ARacingGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	ARacingGameGameModeBase();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	/** Class to Spawn */

	UPROPERTY(EditAnywhere, Category = "GameModeVariable")
	TSubclassOf<class ACheckpointCollider> CheckpointColliderBP;

	TArray<class ACheckpointCollider*> CheckpointArray;
	ACheckpointCollider* tempCheckpoint;

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
	int TotalCheckpoints = 7;

	// Positions and Rotations
	FVector Checkpoint1Vector = FVector(36400.f, 2700.f, 20850.f);
	FRotator Checkpoint1Rotator = FRotator(0.f,10.f,0.f);

	FVector Checkpoint2Vector = FVector(9700.f,-8500.f,12650.f);
	FRotator Checkpoint2Rotator = FRotator(0.f,-80.f,0.f);

	FVector Checkpoint3Vector = FVector(15800.f,-27000.f,5450.f);
	FRotator Checkpoint3Rotator = FRotator(0.f,10.f,0.f);

	FVector Checkpoint4Vector = FVector(22700.f,-11500.f,10800.f);
	FRotator Checkpoint4Rotator = FRotator(0.f,-100.f,0.f);

	FVector Checkpoint5Vector = FVector(19800.f,13900.f,17000.f);
	FRotator Checkpoint5Rotator = FRotator(0.f,100.f,0.f);

	FVector Checkpoint6Vector = FVector(9400.f,11700.f,20300.f);
	FRotator Checkpoint6Rotator = FRotator(0.f,20.f,0.f);

	FVector Checkpoint7Vector = FVector(-15100.f,7850.f,22600.f);
	FRotator Checkpoint7Rotator = FRotator(0.f,0.f,0.f);

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
	float Section7BestTime;

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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
		float WorldCheckpoint7;
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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
		float WorldCheckpoint14;
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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
		float WorldCheckpoint21;

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
	void RespawnItems();


	/** Used for countdown before start */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameModeVariable")
	int SecondsUntilStart = 3;

	float OneSecond = 1.f;
	float PreGameClock = 0.f;




};
