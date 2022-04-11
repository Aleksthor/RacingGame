// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EggBaskets.generated.h"

UCLASS()
class RACINGGAME_API AEggBaskets : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEggBaskets();

	/** Collision Box */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EggBasketVariables")
	class USphereComponent* Collider{ nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EggBasketVariables")
	USphereComponent* MagnetCollider { nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EggBasketVariables")
	class UStaticMeshComponent* EggBasketMesh{ nullptr };


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EggBasketVariables")
	int ReloadAmount = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpeedBoostVariables")
	FVector StartLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpeedBoostVariables")
	FRotator StartRotation;

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

	bool Round2 = false;

	bool Round3 = false;

};
