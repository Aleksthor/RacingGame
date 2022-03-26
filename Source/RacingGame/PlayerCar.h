// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerCar.generated.h"

class UHoverComponent;
class ABomb;

UCLASS()
class RACINGGAME_API APlayerCar : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerCar();

	/** Component Body */
	/** Skeletal Mesh */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables")
	class USkeletalMeshComponent* PlayerMesh{ nullptr };

	/** Collision Box */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables")
	class UBoxComponent* Collider{ nullptr };

	/** Spring Arm */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables")
	class USpringArmComponent* SpringArm{ nullptr };

	/** Camera */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables")
	class UCameraComponent* Camera{ nullptr };

	//** MovementComponent */
	UPROPERTY(VisibleAnywhere)
	class UPawnMovementComponent* MovementComponent;

	/** Hover Components | Line trace by channel and Add Force */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables")
	UHoverComponent* HoverComponent1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables")
	UHoverComponent* HoverComponent2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables")
	UHoverComponent* HoverComponent3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables")
	UHoverComponent* HoverComponent4;


	/** Classes that we set in blueprints */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables")
	TSubclassOf<ABomb> BombBP;


	/** LOGIC */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerVariables | Logic")
	bool bDrifting = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerVariables | Logic")
	bool bSpeedBoost = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerVariables | Logic")
	float SpeedBoostTimer = 2.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerVariables | Logic")
	float SpeedBoostClock = 0.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerVariables | Logic")
	float SpeedBoostSpeed = 3500.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerVariables | Logic")
	float CheckpointTimer = 2.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerVariables | Logic")
	float CheckpointClock = 0.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerVariables | Logic")
	float DriftValue;
	


	/** Constructor Values | Also used later for reference to default values */


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables | Defaults")
	float PlayerMaxSpeed = 2500.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	


	

	/** Input Functions */
	

	UFUNCTION()
	void Forward(float value);

	UFUNCTION()
	void Right(float value);

	UFUNCTION()
	void Pause(float value);

	UFUNCTION()
	void StartDrift();

	UFUNCTION()
	void StopDrift();

	UFUNCTION()
	void StartShooting();

	UFUNCTION()
	void StopShooting();

	/** Tick Functions */

	UFUNCTION()
	void doTimerTick();

	UFUNCTION()
	void UpdateRotation(float Delta);

	UFUNCTION()
	void CheckImpactPoints();

	UFUNCTION()
	void UpdateMaxSpeed(float Delta);

	UFUNCTION()
	void UpdateCheckpointTimer(float Delta);

	// Used in UpdateClocks()
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerVariables | Tick")
	int WorldMinutes;

	// Used in UpdateClocks()
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerVariables | Tick")
	int SectionMinutes;

	// Used in UpdateClocks()
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerVariables | Tick")
	int SectionAggregateSeconds;

	// Save Pawn Rotation Every Tick
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerVariables | Tick")
	FRotator PawnRotation;

	// Save Control Rotation Every Tick
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerVariables | Tick")
	FRotator ControlRotation;

	// The set rotator, altered in Right() | Input Function
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerVariables | Tick")
	FRotator NewRotation;
	
	/** Functions used by other classes */

	void SetLastCheckPointTimer();

	UFUNCTION()
	void LoseHealth();

	UFUNCTION()
	void GivePoints(int Value);



	/** Player Variables that HUD access */
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables | HUD")
	float WorldTimer;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables | HUD")
	float WorldTimer_Local;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables | HUD")
	float SectionTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables | HUD")
	float SectionAggregate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables | HUD")
	float LastCheckPointTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables | HUD")
	float LastCheckPointSectionTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables | HUD")
	float LastCheckPointSectionTimerAggregate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables | HUD")
	bool bJustHitCheckPoint = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables | HUD")
	int Points;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables | HUD")
	int Lives;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables | HUD")
	bool bDead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables | HUD")
	bool bGameOver = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables | HUD")
	bool bGameStarted = false;

	
};
