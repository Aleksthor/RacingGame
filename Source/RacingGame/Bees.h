// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Bees.generated.h"

class USphereComponent;

UCLASS()
class RACINGGAME_API ABees : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABees();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeeVariables")
	class UCapsuleComponent* Root;

	// The Sphere Collider that initiates Pathfinding
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeeVariables")
	USphereComponent* PlayerDetectionCollider { nullptr };

	// The Sphere Collider that initiates Pathfinding
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeeVariables")
	USphereComponent* HealthCollider { nullptr };

	// The Sphere Collider that initiates Pathfinding
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeeVariables")
	USphereComponent* AttackCollider {nullptr};

	// Controller that gives AI inputs
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeeVariables")
	class AAIController* AIController{ nullptr };

	// Mesh Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeeVariables")
	class UStaticMeshComponent* BeeMesh{ nullptr };


	// MovementComponent 
	UPROPERTY(VisibleAnywhere)
	class UPawnMovementComponent* MovementComponent;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	/** Booleans */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeeVariables | Logic")
	bool bMad = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeeVariables | Logic")
	bool bAttacking = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeeVariables | Logic")
	bool bDead = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeeVariables | Logic")
	bool bGivenDamage = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeeVariables | Logic")
	bool bCanGiveDamage = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeeVariables | Logic")
	bool bOverlapping = false;

	/** Floats */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeeVariables | Logic")
	float DamageClock = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeeVariables | Logic")
	float DamageTimer = 1.f;

	/** Functions */

	UFUNCTION()
	void OnOverlapDetection(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEndDetection(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);

	UFUNCTION()
	void OnOverlapHealth(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapAttack(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEndAttack(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);
};
