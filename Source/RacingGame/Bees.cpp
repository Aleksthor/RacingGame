// Fill out your copyright notice in the Description page of Project Settings.


#include "Bees.h"
#include "Target.h"
#include "Components/SphereComponent.h"

#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/PawnMovementComponent.h"
#include "PlayerCar.h"
#include "Bomb.h"
#include "AIController.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
ABees::ABees()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthCollider = CreateDefaultSubobject<USphereComponent>(TEXT("HealthCollider"));
	SetRootComponent(HealthCollider);
	HealthCollider->InitSphereRadius(25.f);
	
	PlayerDetectionCollider = CreateDefaultSubobject<USphereComponent>(TEXT("PlayerDetectionCollider"));
	PlayerDetectionCollider->SetupAttachment(GetRootComponent());
	PlayerDetectionCollider->InitSphereRadius(4000.f);

	

	AttackCollider = CreateDefaultSubobject<USphereComponent>(TEXT("AttackCollider"));
	AttackCollider->SetupAttachment(GetRootComponent());
	AttackCollider->InitSphereRadius(60.f);

	/** Movement Component Default Values*/
	MovementComponent = CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>(TEXT("MovementComponent"));
	MovementComponent->UpdatedComponent = GetRootComponent();
	Cast<UFloatingPawnMovement>(MovementComponent)->MaxSpeed = 2000.f;
	

	BeeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BeeMesh"));
	BeeMesh->SetupAttachment(GetRootComponent());


	
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void ABees::BeginPlay()
{
	Super::BeginPlay();
	
	AIController = Cast<AAIController>(GetController());

	PlayerDetectionCollider->OnComponentBeginOverlap.AddDynamic(this, &ABees::OnOverlapDetection);
	PlayerDetectionCollider->OnComponentEndOverlap.AddDynamic(this, &ABees::OnOverlapEndDetection);

	HealthCollider->OnComponentBeginOverlap.AddDynamic(this, &ABees::OnOverlapHealth);

	AttackCollider->OnComponentBeginOverlap.AddDynamic(this, &ABees::OnOverlapAttack);
	AttackCollider->OnComponentEndOverlap.AddDynamic(this, &ABees::OnOverlapEndAttack);
}

// Called every frame
void ABees::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bGivenDamage)
	{
		bCanGiveDamage = false;
		DamageClock += DeltaTime;

		if (DamageClock > DamageTimer)
		{
			DamageClock = 0.f;
			bCanGiveDamage = true;
			bGivenDamage = false;
		}
	}
	if (bAttacking)
	{
		if (bCanGiveDamage)
		{
			APawn* Pawn = GetWorld()->GetFirstPlayerController()->GetPawn();
			APlayerCar* Player = Cast<APlayerCar>(Pawn);
			Player->LoseHealth();
			bGivenDamage = true;
		}
	}
	// Some Random Movement if enemy is not targeting player
	FVector CurrentLocation = GetActorLocation();
	if (!bOverlapping)
	{
		RoamClock += DeltaTime;

		if (RoamClock > RoamTimer)
		{
			FVector Rand = FVector(0.f, 0.f, CurrentLocation.Z);
			Rand.X = FMath::FRandRange(CurrentLocation.X - 500.f, CurrentLocation.X + 500.f);
			Rand.Y = FMath::FRandRange(CurrentLocation.Y - 500.f, CurrentLocation.Y + 500.f);

			AIController->MoveTo(Rand);
			RoamClock = 0.f;
		}
	}

	if (bOverlapping)
	{
		APawn* Pawn = GetWorld()->GetFirstPlayerController()->GetPawn();
		APlayerCar* Player = Cast<APlayerCar>(Pawn);

		AIController->MoveToActor(Player, 10.f);
		


	}

	
	
}

// Called to bind functionality to input
void ABees::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABees::OnOverlapDetection(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCar* Player = Cast<APlayerCar>(OtherActor);
	if (Player && AIController)
	{
		bOverlapping = true;
		AIController->SetFocus(Player);
	}
}

void ABees::OnOverlapEndDetection(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	APlayerCar* Player = Cast<APlayerCar>(OtherActor);
	if (AIController && Player)
	{
		bOverlapping = false;
		AIController->StopMovement();
		AIController->ClearFocus(EAIFocusPriority::Gameplay);
	}
}

void ABees::OnOverlapHealth(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABomb* Bomb = Cast<ABomb>(OtherActor);
	if (Bomb)
	{
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
		bDead = true;
	}
	
}

void ABees::OnOverlapAttack(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	APlayerCar* Player = Cast<APlayerCar>(OtherActor);
	if (Player )
	{
		bAttacking = true;
	}
}

void ABees::OnOverlapEndAttack(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	APlayerCar* Player = Cast<APlayerCar>(OtherActor);
	if (Player)
	{
		bAttacking = false;
		bCanGiveDamage = true;
		DamageClock = 0.f;
	}
}

