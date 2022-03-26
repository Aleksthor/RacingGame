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
