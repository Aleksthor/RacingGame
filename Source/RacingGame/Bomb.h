// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bomb.generated.h"

UCLASS()
class RACINGGAME_API ABomb : public AActor
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this actor's properties
	ABomb();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BombVariables")
	class USphereComponent* Collider{ nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BombVariables")
	class UStaticMeshComponent* BombMesh;


	class APlayerCar* Player{nullptr};

	float Force;
	bool bAddedForce = false;

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


	/** If bullet hits something that destroys itself, also destroy bomb */
	UFUNCTION()
	void DestroyBomb();



};
