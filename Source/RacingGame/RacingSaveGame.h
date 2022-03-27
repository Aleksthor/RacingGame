// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "RacingSaveGame.generated.h"

USTRUCT(BlueprintType)
struct FLevelStats
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	FString LevelName;

	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	float Section1Best;

	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	float Section2Best;

	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	float Section3Best;

	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	float Section4Best;

	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	float Section5Best;

	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	float Section6Best;

	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	float Section7Best;

	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	float RoundBest;

	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	float TotalBest;


	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	float WorldCheckpoint1Best;
	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	float WorldCheckpoint2Best;
	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	float WorldCheckpoint3Best;
	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	float WorldCheckpoint4Best;
	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	float WorldCheckpoint5Best;
	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	float WorldCheckpoint6Best;
	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	float WorldCheckpoint7Best;
	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	float WorldCheckpoint8Best;
	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	float WorldCheckpoint9Best;
	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	float WorldCheckpoint10Best;
	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	float WorldCheckpoint11Best;
	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	float WorldCheckpoint12Best;
	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	float WorldCheckpoint13Best;
	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	float WorldCheckpoint14Best;
	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	float WorldCheckpoint15Best;
	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	float WorldCheckpoint16Best;
	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	float WorldCheckpoint17Best;
	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	float WorldCheckpoint18Best;
	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	float WorldCheckpoint19Best;
	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	float WorldCheckpoint20Best;
	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	float WorldCheckpoint21Best;

};

/**
 * 
 */
UCLASS()
class RACINGGAME_API URacingSaveGame : public USaveGame
{
	GENERATED_BODY()


public:

	URacingSaveGame();

	UPROPERTY(VisibleAnywhere,Category = Basic)
	FString PlayerName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	uint32 UserIndex;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FLevelStats Level1Stats;

};
