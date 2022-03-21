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
	class UBoxComponent* Collider{ nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpeedBoostVariables")
	class UStaticMeshComponent* SpeedBoostMesh{ nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpeedBoostVariables")
	float Speed = 3500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpeedBoostVariables")
	float Timer = 2.f;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
