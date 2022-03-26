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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables")
	UHoverComponent* HoverComponent1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables")
	UHoverComponent* HoverComponent2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables")
	UHoverComponent* HoverComponent3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables")
	UHoverComponent* HoverComponent4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables")
	TSubclassOf<ABomb> BombBP;


	// Logic

	bool bDrifting = false;
	bool bSpeedBoost = false;
	float SpeedBoostTimer = 2.f;
	float SpeedBoostClock = 0.f;
	float SpeedBoostSpeed = 3500.f;
	float CheckpointTimer = 2.f;
	float CheckpointClock = 0.f;
	float DriftValue;

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	// Save Pawn Rotation Every Tick
	FRotator PawnRotation;

	// Save Control Rotation Every Tick
	FRotator ControlRotation;


	FRotator NewRotation;

	

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



	void CheckImpactPoints();

	void SetLastCheckPointTimer();

	UFUNCTION()
	void LoseHealth();

	UFUNCTION()
	void GivePoints(int Value);


	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables | HUD")
	float WorldTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables | HUD")
	float SectionTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables | HUD")
	FString HUDTimerWorld;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables | HUD")
	FString HUDTimerSection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables | HUD")
	FString LastCheckPointTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables | HUD")
	bool bJustHitCheckPoint = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables | HUD")
	int Points;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables | HUD")
	int Lives;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables | HUD")
	bool bDead;

	bool bEnd = false;
	int WorldMinutes;
	int SectionMinutes;
	
};
