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


	UPROPERTY(EditAnywhere, Category = "GameModeVariable")
	TSubclassOf<class ACheckpointCollider> CheckpointColliderBP;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameModeVariable")
	int TotalCheckpoints = 7;

	int CurrentCheckpoint = 0;
	
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


	TArray<class ACheckpointCollider*> CheckpointArray;
	ACheckpointCollider* tempEnemy;

	class APlayerCar* Player{ nullptr };


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameModeVariable")
	FString PlayerName;


	UFUNCTION()
	void GameWon();

	UFUNCTION()
	void Reset();

	UFUNCTION(BlueprintCallable)
	void LoadMap1();



	float OneSecond = 1.f;
	float PreGameClock = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameModeVariable")
	int SecondsUntilStart = 3;
	

};
