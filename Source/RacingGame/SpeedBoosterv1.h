// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpeedBoosterv1.generated.h"

UCLASS()
class RACINGGAME_API ASpeedBoosterv1 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpeedBoosterv1();


	/** Collision Box */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpeedBoostVariables")
	class USphereComponent* Collider{ nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpeedBoostVariables")
	USphereComponent* MagnetCollider{ nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpeedBoostVariables")
	class UStaticMeshComponent* SpeedBoostMesh{ nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpeedBoostVariables")
	float SpeedGiven = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpeedBoostVariables")
	float Timer = 2.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpeedBoostVariables")
	bool isHit = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpeedBoostVariables")
	FVector StartLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpeedBoostVariables")
	FRotator StartRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpeedBoostVariables")
	class USoundCue* OnHitSound{ nullptr };
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

	bool bMagnetPull = false;

	float InterSpeed = 10.f;
};
