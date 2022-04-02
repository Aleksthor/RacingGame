// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Target.generated.h"

class UStaticMesh;

UCLASS()
class RACINGGAME_API ATarget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATarget();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TargetVariables")
	class USphereComponent* Collider{ nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TargetVariables")
	class UStaticMeshComponent* TargetMesh;

	class APlayerCar* Player{ nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TargetVariables")
	UStaticMesh* RedMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TargetVariables")
	UStaticMesh* BlueMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TargetVariables")
	UStaticMesh* YellowMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TargetVariables")
	class USoundCue* OnHitSound{ nullptr };

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
	void DestroyTarget();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TargetVariables")
	int PointsGiven;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TargetVariables")
	float SpeedGiven;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TargetVariables")
	float SpeedboostTimer = 3.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TargetVariables")
	float RotationSpeed = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TargetVariables")
	bool isHit = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TargetVariables")
	FVector Top;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TargetVariables")
	FVector Bottom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TargetVariables")
	bool GoingUp = true;
	
};
