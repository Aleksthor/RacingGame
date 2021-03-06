// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Points.generated.h"

UCLASS()
class RACINGGAME_API APoints : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APoints();


	/** Collision Box */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PointsVariables")
	class USphereComponent* Collider{ nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PointsVariables")
	USphereComponent* MagnetCollider { nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PointsVariables")
	class UStaticMeshComponent* PointsMesh{ nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PointsVariables")
	float PointsGiven = 20.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PointsVariables")
	bool isHit = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PointsVariables")
	bool Round2 = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PointsVariables")
	bool Round3 = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PointsVariables")
	class USoundCue* OnHitSound1{ nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PointsVariables")
	class USoundCue* OnHitSound2{ nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PointsVariables")
	FVector StartLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PointsVariables")
	FRotator StartRotation;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PointsVariables")
	bool bMagnetPull = false;

	float InterSpeed = 10.f;

};
