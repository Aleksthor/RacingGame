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
	ACheckpointCollider* tempEnemy;

	class APlayerCar* Player{ nullptr };

	/** Default Values */

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
	int CurrentRound = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameModeVariable")
	int CurrentCheckpoint = 0;

	/** Checkpoint Variables*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
	int TotalCheckpoints = 7;

	// Positions and Rotations
	FVector Checkpoint1Vector = FVector(27500.f, 3100.f, 23350.f);
	FRotator Checkpoint1Rotator = FRotator(0.f,100.f,0.f);

	FVector Checkpoint2Vector = FVector(20100.f,400.f,15250.f);
	FRotator Checkpoint2Rotator = FRotator(0.f,90.f,0.f);

	FVector Checkpoint3Vector = FVector(8400.f,-17000.f,8500.f);
	FRotator Checkpoint3Rotator = FRotator(0.f,60.f,0.f);

	FVector Checkpoint4Vector = FVector(22700.f,-11500.f,10800.f);
	FRotator Checkpoint4Rotator = FRotator(0.f,-100.f,0.f);

	FVector Checkpoint5Vector = FVector(19800.f,13900.f,17800.f);
	FRotator Checkpoint5Rotator = FRotator(0.f,100.f,0.f);

	FVector Checkpoint6Vector = FVector(9400.f,11700.f,20300.f);
	FRotator Checkpoint6Rotator = FRotator(0.f,20.f,0.f);

	FVector Checkpoint7Vector = FVector(4800.f,6250.f,25000.f);
	FRotator Checkpoint7Rotator = FRotator(0.f,-100.f,0.f);

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

	/** Functions */

	UFUNCTION()
	void GameWon();

	UFUNCTION()
	void Reset();

	UFUNCTION(BlueprintCallable)
	void LoadMap1();



	/** Used for countdown before start */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameModeVariable")
	int SecondsUntilStart = 3;

	float OneSecond = 1.f;
	float PreGameClock = 0.f;

};
