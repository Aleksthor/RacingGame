// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCar.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/PlayerInput.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "HoverComponent.h"
#include "Bomb.h"
#include "Engine/World.h"
#include "RacingGameGameModeBase.h"
#include "HealthPack.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetTextLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

// Sets default values
APlayerCar::APlayerCar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	/** Collider Default Values */
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	SetRootComponent(Collider);
	Collider->SetSimulatePhysics(true);
	Collider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Collider->SetCollisionProfileName(FName(TEXT("Pawn")));
	//Collider->OnComponentBeginOverlap.AddDynamic(this, &APlayerCar::OnOverlap);


	/** Player Mesh Default Values */
	PlayerMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PlayerMesh"));
	PlayerMesh->SetupAttachment(Collider);
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> Mesh(TEXT("SkeletalMesh'/Game/Meshes/Ducky/ducky2.ducky2'"));
	PlayerMesh->SetSkeletalMesh(Mesh.Object);
	PlayerMesh->SetRelativeScale3D(FVector(50.f, 50.f, 50.f));
	PlayerMesh->SetRelativeLocation(FVector(0.f, 10.f, -40.f));
	PlayerMesh->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));

	/** Spring Arm Default Values */
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->TargetArmLength = 600.f;
	SpringArm->SetupAttachment(Collider);
	SpringArm->bDoCollisionTest = false;
	SpringArm->SetRelativeRotation(FRotator(-15.f, 0.f, 0.f));
	SpringArm->bUsePawnControlRotation = true;

	/** Movement Component Default Values*/
	MovementComponent = CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>(TEXT("MovementComponent"));
	MovementComponent->UpdatedComponent = Collider;
	

	HoverComponent1 = CreateDefaultSubobject<UHoverComponent>(TEXT("HoverComponent1"));
	HoverComponent1->SetupAttachment(Collider);
	HoverComponent1->SetRelativeLocation(FVector(60.f, 60.f, 0.f));

	HoverComponent2 = CreateDefaultSubobject<UHoverComponent>(TEXT("HoverComponent2"));
	HoverComponent2->SetupAttachment(Collider);
	HoverComponent2->SetRelativeLocation(FVector(60.f, -60.f, 0.f));

	HoverComponent3 = CreateDefaultSubobject<UHoverComponent>(TEXT("HoverComponent3"));
	HoverComponent3->SetupAttachment(Collider);
	HoverComponent3->SetRelativeLocation(FVector(-60.f, 60.f, 0.f));

	HoverComponent4 = CreateDefaultSubobject<UHoverComponent>(TEXT("HoverComponent4"));
	HoverComponent4->SetupAttachment(Collider);
	HoverComponent4->SetRelativeLocation(FVector(-60.f, -60.f, 0.f));

	/** Attaching Camera to the SpringArm*/
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	Cast<UFloatingPawnMovement>(MovementComponent)->MaxSpeed = PlayerMaxSpeed;

	Lives = 3;
	bDead = false;
	
	
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void APlayerCar::BeginPlay()
{
	Super::BeginPlay();
	
	Points = 0;
	AGameModeBase* GameModeBase = GetWorld()->GetAuthGameMode();
	if (FMath::IsNearlyZero(Cast<ARacingGameGameModeBase>(GameModeBase)->WorldCheckpoint1))
	{
		FirstRun = true;
	}

	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), "DisableAllScreenMessages");
}

// Called every frame
void APlayerCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	doTimerTick();

	//UpdateClocks();
	

	PawnRotation = GetActorRotation();
	ControlRotation = GetControlRotation();

	UpdateRotation(DeltaTime);

	UpdateMaxSpeed(DeltaTime);
	
	UpdateCheckpointTimer(DeltaTime);

	if (Lives > 6)
	{
		Lives = 6;
	}


	if (Lives == 0)
	{
		bDead = true;
	}

	if (!CanSpawnHealthPack)
	{
		SpawnHealthPackClock += DeltaTime;

		if (SpawnHealthPackClock > SpawnHealthPackTimer)
		{
			SpawnHealthPackClock = 0.f;
			CanSpawnHealthPack = true;
		}
	}
	if (ControllerPitchStill && ControllerYawStill)
	{

		ControllerStillClock += DeltaTime;

		if (ControllerStillClock > ControllerStillTimer)
		{
			
			if (SpringArm->bUsePawnControlRotation)
			{
				SpringArm->SetWorldRotation(FRotator(ControlRotation.Pitch, ControlRotation.Yaw , ControlRotation.Roll));
				SpringArm->bUsePawnControlRotation = false;
			
			}
		

			FRotator SpringArmRotator = FMath::RInterpTo(SpringArm->GetRelativeRotation(), FRotator(-15.f, 0.f, 0.f), UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), 2.f);
			Controller->SetControlRotation(SpringArm->GetComponentRotation());
			SpringArm->SetRelativeRotation(SpringArmRotator);
		}

	
	}


	if (!bCanShoot)
	{
		CanShootClock += DeltaTime;

		if (CanShootClock > CanShootTimer)
		{
			CanShootClock = 0.f;
			bCanShoot = true;
			TryToShoot = false;
		}
	}

}


// Called to bind functionality to input
void APlayerCar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Forward", this, &APlayerCar::Forward);
	PlayerInputComponent->BindAxis("Right", this, &APlayerCar::Right);

	PlayerInputComponent->BindAction("ShootHigh", IE_Pressed, this, &APlayerCar::StartShooting);
	PlayerInputComponent->BindAction("ShootHigh", IE_Released, this, &APlayerCar::StopShooting);

	// Turn Camera with mouse
	PlayerInputComponent->BindAxis("TurnCamera", this, &APlayerCar::TurnCamera);
	PlayerInputComponent->BindAxis("LookUpCamera", this, &APlayerCar::LookUpCamera);

	PlayerInputComponent->BindAction("Drift", IE_Pressed, this, &APlayerCar::StartDrift);
	PlayerInputComponent->BindAction("Drift", IE_Released, this, &APlayerCar::StopDrift);
}


/** Input Functions */

void APlayerCar::Forward(float value)
{
	FVector RotationVector = FRotationMatrix(PawnRotation).GetUnitAxis(EAxis::X);
	FVector ZRotation = PawnRotation.Vector();
	FVector Direction = FVector(RotationVector.X, RotationVector.Y, ZRotation.Z);

	if (bGameStarted)
	{
		AddMovementInput(Direction, value);
	}

	
}

void APlayerCar::Right(float value)
{
	DriftValue = value;
	float factor;
	if (bDrifting)
	{
		
	
		factor = 0.3;

	}
	else
	{
		factor = 0.2;
	}



	FVector AsymVector = GetActorRightVector() * value;
	FVector NewRotationVector = GetActorForwardVector() + AsymVector * factor;
	NewRotation = NewRotationVector.Rotation();

}

void APlayerCar::LookUpCamera(float value)
{
	if (value == 0.f)
	{
		
		ControllerPitchStill = true;
	}
	else
	{
		ControllerStillClock = 0.f;
		SpringArm->bUsePawnControlRotation = true;
		ControllerPitchStill = false;
		AddControllerPitchInput(value);
	}
}

void APlayerCar::TurnCamera(float value)
{


	if (value == 0.f)
	{
		
		ControllerYawStill = true;
	}
	else
	{
		ControllerStillClock = 0.f;
		SpringArm->bUsePawnControlRotation = true;
		ControllerYawStill = false;
		AddControllerYawInput(value);
	}

}

void APlayerCar::Pause()
{
}

void APlayerCar::StartDrift()
{
	bDrifting = true;
}

void APlayerCar::StopDrift()
{
	bDrifting = false;
}

void APlayerCar::StartShooting()
{
	
	if (bCanShoot)
	{
		if (ShootSound)
		{
			UGameplayStatics::PlaySound2D(this, ShootSound);
		}
		GetWorld()->SpawnActor<ABomb>(BombBP, GetActorLocation() + GetActorForwardVector() * 100.f, FRotator(0.f, PlayerMesh->GetComponentRotation().Yaw, 0.f));
		bCanShoot = false;
	}
	else
	{
		TryToShoot = true;
	}
	
	
}

void APlayerCar::StopShooting()
{


}




/** Tick Functions */


void APlayerCar::doTimerTick()
{
	if (bGameStarted && !bGameOver)
	{
		// Track timers for the whole track and all sections
		WorldTimer += UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
		SectionTimer += UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
	}
}


void APlayerCar::UpdateRotation(float Delta)
{
	FRotator SetRotation;
	if (FMath::IsNearlyEqual(DriftValue, 0.f))
	{
		SetRotation = FMath::RInterpTo(PlayerMesh->GetRelativeRotation(), FRotator(0.f, 180.f, 0.f), Delta, 5.f);
		PlayerMesh->SetRelativeRotation(SetRotation);
	}


	// Function for Interp Rotation
	if (!MovementComponent->Velocity.IsNearlyZero())
	{
		PawnRotation = GetActorRotation();

		FRotator Yaw = FMath::RInterpTo(PawnRotation, NewRotation, Delta, 5.f);

		CheckImpactPoints(Delta);


		if (DriftValue > 0.f)
		{
			FRotator SteerAngle = FRotator(0.f, -170.f, -10.f);
			SetRotation = FMath::RInterpTo(PlayerMesh->GetRelativeRotation(), SteerAngle, Delta, 5.f);

		}
		else if (DriftValue < 0.f)
		{
			FRotator SteerAngle = FRotator(0.f, 170.f, 10.f);
			SetRotation = FMath::RInterpTo(PlayerMesh->GetRelativeRotation(), SteerAngle, Delta, 5.f);
		}
		else if (FMath::IsNearlyZero(DriftValue))
		{
			FRotator SteerAngle = FRotator(0.f, 180.f, 0.f);
			SetRotation = FMath::RInterpTo(PlayerMesh->GetRelativeRotation(), SteerAngle, Delta, 5.f);
		}
		SetActorRotation(FRotator(UseRotation.Pitch, Yaw.Yaw, UseRotation.Roll));
		PlayerMesh->SetRelativeRotation(SetRotation);
	}

	if (bDrifting)
	{
		if (!FMath::IsNearlyZero(DriftValue))
		{
			FRotator DriftAngle;
			if (DriftValue > 0.f)
			{
				DriftAngle = FRotator(0.f, -160.f, -15.f);
			}
			else
			{
				DriftAngle = FRotator(0.f, 160.f, 15.f);
			}

			SetRotation = FMath::RInterpTo(PlayerMesh->GetRelativeRotation(), DriftAngle, Delta, 5.f);


			PlayerMesh->SetRelativeRotation(SetRotation);
			//UE_LOG(LogTemp, Warning, TEXT("%f"), SetRotation.Yaw);
		}

	}
}

void APlayerCar::UpdateMaxSpeed(float Delta)
{
	CurrentSpeed = Cast<UFloatingPawnMovement>(MovementComponent)->MaxSpeed;

	if (bSpeedBoost)
	{

		SpeedBoostClock += Delta;
		if (SpeedBoostClock > SpeedBoostTimer)
		{
			SpeedBoostClock = 0.f;
			bSpeedBoost = false;
			SpeedBoostTimer = 0.f;
		}
		if (MovementComponent)
		{
		
		float SetSpeed = FMath::FInterpTo(Cast<UFloatingPawnMovement>(MovementComponent)->MaxSpeed, SpeedBoostSpeed, Delta, 10.f);
		Cast<UFloatingPawnMovement>(MovementComponent)->MaxSpeed = SetSpeed;

		}
		
	}
	else
	{
		if (MovementComponent)
		{
			SpeedBoostSpeed = PlayerMaxSpeed;
			float SetSpeed = FMath::FInterpTo(Cast<UFloatingPawnMovement>(MovementComponent)->MaxSpeed, PlayerMaxSpeed, Delta, 1.f);
			Cast<UFloatingPawnMovement>(MovementComponent)->MaxSpeed = SetSpeed;

		}
	}


}

void APlayerCar::UpdateCheckpointTimer(float Delta)
{
	if (bJustHitCheckPoint)
	{
		CheckpointClock += Delta;

		if (CheckpointClock > CheckpointTimer)
		{

			bJustHitCheckPoint = false;
			CheckpointClock = 0.f;
		}


	}
}

void APlayerCar::CheckImpactPoints(float Delta)
{
	// Function to make sure gravity works while in air - Only call when moving

	FVector ImpactPoints1 = HoverComponent1->HitResult.ImpactPoint;
	FVector ImpactPoints2 = HoverComponent2->HitResult.ImpactPoint;
	FVector ImpactPoints3 = HoverComponent3->HitResult.ImpactPoint;
	FVector ImpactPoints4 = HoverComponent4->HitResult.ImpactPoint;

	if (ImpactPoints1.IsNearlyZero() && ImpactPoints2.IsNearlyZero() && ImpactPoints3.IsNearlyZero() && ImpactPoints4.IsNearlyZero())
	{

		InAirClock += Delta;

		if (InAirClock > InAirTimer)
		{
			UseRotation = FMath::RInterpTo(PawnRotation, FRotator::ZeroRotator, Delta, 1.5f);

		}

	
		
		
		HoverComponent1->LinearDamping = 0.f;
		HoverComponent2->LinearDamping = 0.f;
		HoverComponent3->LinearDamping = 0.f;
		HoverComponent4->LinearDamping = 0.f;

		HoverComponent1->AngularDamping = 1.f;
		HoverComponent2->AngularDamping = 1.f;
		HoverComponent3->AngularDamping = 1.f;
		HoverComponent4->AngularDamping = 1.f;

		
	}
	else
	{
		InAirClock = 0.f;
		UseRotation.Pitch = PawnRotation.Pitch;
		UseRotation.Roll = PawnRotation.Roll;
		HoverComponent1->LinearDamping = HoverComponent1->LinearDampingDefault;
		HoverComponent2->LinearDamping = HoverComponent2->LinearDampingDefault;
		HoverComponent3->LinearDamping = HoverComponent3->LinearDampingDefault;
		HoverComponent4->LinearDamping = HoverComponent4->LinearDampingDefault;

		HoverComponent1->AngularDamping = HoverComponent1->AngularDampingDefault;
		HoverComponent2->AngularDamping = HoverComponent2->AngularDampingDefault;
		HoverComponent3->AngularDamping = HoverComponent3->AngularDampingDefault;
		HoverComponent4->AngularDamping = HoverComponent4->AngularDampingDefault;
	}

}


/** Functions used by other classes */

void APlayerCar::SetLastCheckPointTimer()
{

	LastCheckPointSectionTimer = SectionTimer;
	LastCheckPointTimer = WorldTimer;

}

void APlayerCar::LoseHealth()
{
	if (CanSpawnHealthPack)
	{
		GetWorld()->SpawnActor<AHealthPack>(HealthPackBP, GetActorLocation() - GetActorForwardVector() * 200.f, FRotator(0.f, PlayerMesh->GetComponentRotation().Yaw, 0.f));
		CanSpawnHealthPack = false;
	}
	if (Lives > 0)
	{
		Lives--;
	}
	

}

void APlayerCar::GivePoints(int Value)
{
	Points += Value;
}


