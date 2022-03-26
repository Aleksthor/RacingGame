// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CheckpointCollider.generated.h"

UCLASS()
class RACINGGAME_API ACheckpointCollider : public AActor
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this actor's properties
	ACheckpointCollider();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CheckpointVariables")
	class UBoxComponent* Collider{ nullptr };

	
	float ShowTimer;

	class APlayerCar* Player{ nullptr };

	float BestTimer;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CheckpointVariables")
	bool isHit = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CheckpointVariables")
	bool isValid = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);

};
