// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Clock.generated.h"

UCLASS()
class RACINGGAME_API AClock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AClock();

	/** Collision Box */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ClockVariables")
	class USphereComponent* Collider{ nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ClockVariables")
	USphereComponent* MagnetCollider { nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ClockVariables")
	class UStaticMeshComponent* ClockMesh{ nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ClockVariables")
	float TimeGiven = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ClockVariables")
	bool isHit = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ClockVariables")
	bool Round2 = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ClockVariables")
	bool Round3 = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ClockVariables")
	class USoundCue* OnHitSound1{ nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ClockVariables")
	FVector StartLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ClockVariables")
	FRotator StartRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ClockVariables")
	bool bMagnetPull = false;

	float InterSpeed = 10.f;

	class ARacingGameGameModeBase* GameModeBase;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void MagnetOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void MagnetOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);

};
