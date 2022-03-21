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
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> Mesh(TEXT("SkeletalMesh'/Game/Meshes/Ducky/ducky.ducky'"));
	PlayerMesh->SetSkeletalMesh(Mesh.Object);
	PlayerMesh->SetRelativeScale3D(FVector(50.f, 50.f, 50.f));
	PlayerMesh->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	PlayerMesh->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));

	/** Spring Arm Default Values */
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->TargetArmLength = 800.f;
	SpringArm->SetupAttachment(Collider);
	SpringArm->bDoCollisionTest = false;
	SpringArm->SetRelativeRotation(FRotator(-25.f, 0.f, 0.f));
	//SpringArm->bUsePawnControlRotation = true;

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

	Cast<UFloatingPawnMovement>(MovementComponent)->MaxSpeed = 2500.f;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void APlayerCar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PawnRotation = GetActorRotation();
	ControlRotation = GetControlRotation();
	FRotator SetRotation;
	if (FMath::IsNearlyEqual(DriftValue, 0.f))
	{
		SetRotation = FMath::RInterpTo(PlayerMesh->GetRelativeRotation(),FRotator(0.f, 180.f, 0.f),DeltaTime,5.f);
		PlayerMesh->SetRelativeRotation(SetRotation);
	}
	
	// Function for Interp Rotation
	if (!MovementComponent->Velocity.IsNearlyZero())
	{
		PawnRotation = GetActorRotation();

		FRotator Yaw = FMath::RInterpTo(PawnRotation, NewRotation, DeltaTime, 5.f);
		
		// Function to make sure gravity works while in air - Only call when moving

		FVector ImpactPoints1 = HoverComponent1->HitResult.ImpactPoint;
		FVector ImpactPoints2 = HoverComponent2->HitResult.ImpactPoint;
		FVector ImpactPoints3 = HoverComponent3->HitResult.ImpactPoint;
		FVector ImpactPoints4 = HoverComponent4->HitResult.ImpactPoint;
		
		if (ImpactPoints1.IsNearlyZero() && ImpactPoints2.IsNearlyZero() && ImpactPoints3.IsNearlyZero() && ImpactPoints4.IsNearlyZero())
		{
			//UseRotator = FMath::RInterpTo(PawnRotation, FRotator(0.f, 180.f, 0.f), DeltaTime, 5.f);
		
			//UE_LOG(LogTemp, Warning, TEXT("HoverComponent In Air"));
			HoverComponent1->LinearDamping = 1.f;
			HoverComponent2->LinearDamping = 1.f;
			HoverComponent3->LinearDamping = 1.f;
			HoverComponent4->LinearDamping = 1.f;

			HoverComponent1->AngularDamping = 1.f;
			HoverComponent2->AngularDamping = 1.f;
			HoverComponent3->AngularDamping = 1.f;
			HoverComponent4->AngularDamping = 1.f;
		}
		else
		{
			//UE_LOG(LogTemp, Warning, TEXT("HoverComponent Default"));
			HoverComponent1->LinearDamping = HoverComponent1->LinearDampingDefault;
			HoverComponent2->LinearDamping = HoverComponent2->LinearDampingDefault;
			HoverComponent3->LinearDamping = HoverComponent3->LinearDampingDefault;
			HoverComponent4->LinearDamping = HoverComponent4->LinearDampingDefault;

			HoverComponent1->AngularDamping = HoverComponent1->AngularDampingDefault;
			HoverComponent2->AngularDamping = HoverComponent2->AngularDampingDefault;
			HoverComponent3->AngularDamping = HoverComponent3->AngularDampingDefault;
			HoverComponent4->AngularDamping = HoverComponent4->AngularDampingDefault;
		}

		if (DriftValue > 0.f)
		{
			FRotator SteerAngle  = FRotator(0.f, -170.f, -10.f);
			SetRotation = FMath::RInterpTo(PlayerMesh->GetRelativeRotation(), SteerAngle, DeltaTime, 5.f);
			
		}
		else if (DriftValue < 0.f)
		{
			FRotator SteerAngle = FRotator(0.f, 170.f, 10.f);
			SetRotation = FMath::RInterpTo(PlayerMesh->GetRelativeRotation(), SteerAngle, DeltaTime, 5.f);
		
		}
		SetActorRotation(FRotator(PawnRotation.Pitch, Yaw.Yaw, PawnRotation.Roll));
		PlayerMesh->SetRelativeRotation(SetRotation);
	}

	if (bDrifting)
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

		SetRotation = FMath::RInterpTo(PlayerMesh->GetRelativeRotation(), DriftAngle, DeltaTime, 5.f);

		
		PlayerMesh->SetRelativeRotation(SetRotation);
		//UE_LOG(LogTemp, Warning, TEXT("%f"), SetRotation.Yaw);
	}

	if (bSpeedBoost)
	{
		Cast<UFloatingPawnMovement>(MovementComponent)->MaxSpeed = SpeedBoostSpeed;
		SpeedBoostClock += DeltaTime;
		if (SpeedBoostClock > SpeedBoostTimer)
		{
			SpeedBoostClock = 0.f;
			bSpeedBoost = false;
		}
	}
	else
	{
		Cast<UFloatingPawnMovement>(MovementComponent)->MaxSpeed = 2500.f;
	}
}


// Called to bind functionality to input
void APlayerCar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Forward", this, &APlayerCar::Forward);
	PlayerInputComponent->BindAxis("Right", this, &APlayerCar::Right);

	// Turn Camera with mouse
	//PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	//PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Drift", IE_Pressed, this, &APlayerCar::StartDrift);
	PlayerInputComponent->BindAction("Drift", IE_Released, this, &APlayerCar::StopDrift);
}

void APlayerCar::Forward(float value)
{
	FVector RotationVector = FRotationMatrix(PawnRotation).GetUnitAxis(EAxis::X);
	FVector ZRotation = PawnRotation.Vector();
	FVector Direction = FVector(RotationVector.X, RotationVector.Y, ZRotation.Z);

	AddMovementInput(Direction, value);
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

void APlayerCar::Pause(float value)
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
