// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerCar.generated.h"

class UHoverComponent;
class ABomb;
class AHealthPack;

UCLASS()
class RACINGGAME_API APlayerCar : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerCar();

	/** Component Body */
	/** Skeletal Mesh */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* PlayerMesh{ nullptr };

	/** Collision Box */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCapsuleComponent* Collider{ nullptr };

	/** Spring Arm */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USpringArmComponent* SpringArm{ nullptr };

	/** Camera */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* Camera{ nullptr };

	//** MovementComponent */
	UPROPERTY(VisibleAnywhere)
	class UPawnMovementComponent* MovementComponent;

	/** Hover Components | Line trace by channel and Add Force */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UHoverComponent* HoverComponent1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UHoverComponent* HoverComponent2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UHoverComponent* HoverComponent3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UHoverComponent* HoverComponent4;


	/** Classes that we set in blueprints */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables")
	TSubclassOf<ABomb> BombBP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables")
	TSubclassOf<AHealthPack> HealthPackBP;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables")
	class USoundCue* ShootSound{ nullptr };

	/** Constructor Values | Also used later for reference to default values */


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables | Defaults")
	float PlayerMaxSpeed = 3000.f;

	/** LOGIC */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerVariables | Logic")
	bool bDrifting = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerVariables | Logic")
	bool bSpeedBoost = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerVariables | Logic")
	float CurrentSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerVariables | Logic")
	float SpeedBoostTimer = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerVariables | Logic")
	float SpeedBoostClock = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerVariables | Logic")
	float SpeedBoostSpeed = PlayerMaxSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerVariables | Logic")
	int SpeedBoostLevel = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerVariables | Logic")
	float CheckpointTimer = 2.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerVariables | Logic")
	float CheckpointClock = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerVariables | Logic")
	float DriftValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerVariables | Logic")
	bool FirstRun = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerVariables | Logic")
	float SpawnHealthPackTimer = 2.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerVariables | Logic")
	float SpawnHealthPackClock = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerVariables | Logic")
	bool CanSpawnHealthPack = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerVariables | Logic")
	bool ControllerYawStill = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerVariables | Logic")
	bool ControllerPitchStill = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerVariables | Logic")
	float ControllerStillClock = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerVariables | Logic")
	float ControllerStillTimer = 0.2f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerVariables | Logic")
	bool bCanShoot = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerVariables | Logic")
	bool TryToShoot = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerVariables | Logic")
	float CanShootClock = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables | Logic")
	float CanShootTimer = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables | Logic")
	float InAirClock = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables | Logic")
	float InAirTimer = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables | Logic")
	bool ResettingCamera = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables | Logic")
	bool LookingBehind = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables | Logic")
	bool bCanNeverShoot = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables | Logic")
	bool bFreelook = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables | Logic")
	float factor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables | Logic")
	bool bLowAmmo = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables | Logic")
	float LowAmmoTimer = 2.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables | Logic")
	float LowAmmoClock = 0.f;

	/** Input Functions */
	

	UFUNCTION()
	void Forward(float value);

	UFUNCTION()
	void Right(float value);


	UFUNCTION()
	void LookUpCamera(float value);


	UFUNCTION()
	void TurnCamera(float value);

	UFUNCTION()
	void Pause();

	UFUNCTION()
	void StartDrift();

	UFUNCTION()
	void StopDrift();

	UFUNCTION()
	void StartShooting();

	UFUNCTION()
	void StopShooting();

	UFUNCTION()
	void ResetCamera();

	UFUNCTION()
	void LookBehind();

	UFUNCTION()
	void ReleaseLookBehind();

	UFUNCTION()
	void Freelook();

	UFUNCTION()
	void ReleaseFreeLook();


	/** Tick Functions */

	UFUNCTION()
	void doTimerTick();

	UFUNCTION()
	void UpdateRotation(float Delta);

	UFUNCTION()
	void CheckImpactPoints(float Delta);

	UFUNCTION()
	void UpdateMaxSpeed(float Delta);

	UFUNCTION()
	void UpdateCheckpointTimer(float Delta);

	UFUNCTION()
	void UpdateCameraRotation(float Delta);


	// Save Pawn Rotation Every Tick
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerVariables | Tick")
	FRotator PawnRotation;

	// Save Control Rotation Every Tick
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerVariables | Tick")
	FRotator ControlRotation;

	// The set rotator, altered in Right() | Input Function
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerVariables | Tick")
	FRotator NewRotation;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerVariables | Tick")
	FRotator UseRotation;

	/** Functions used by other classes */

	void SetLastCheckPointTimer();

	UFUNCTION()
	void LoseHealth();

	UFUNCTION()
	void GivePoints(int Value);

	UFUNCTION()
	void ReloadEggs(int amount);



	/** Player Variables that HUD access */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables | HUD")
	int Ammo = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables | HUD")
	FString LowAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables | HUD")
	bool bNoAmmo = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables | HUD")
	float WorldTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables | HUD")
	float SectionTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables | HUD")
	float SectionAggregate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables | HUD")
	float WorldAggregate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables | HUD")
	FString CurrentSection = "Section 1";

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
