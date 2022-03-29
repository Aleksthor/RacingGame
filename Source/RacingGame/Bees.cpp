// Fill out your copyright notice in the Description page of Project Settings.


#include "Bees.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/PawnMovementComponent.h"
#include "PlayerCar.h"
#include "Bomb.h"
#include "AIController.h"

// Sets default values
ABees::ABees()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Root"));
	SetRootComponent(Root);

	
	PlayerDetectionCollider = CreateDefaultSubobject<USphereComponent>(TEXT("PlayerDetectionCollider"));
	PlayerDetectionCollider->SetupAttachment(RootComponent);
	PlayerDetectionCollider->InitSphereRadius(4000.f);

	HealthCollider = CreateDefaultSubobject<USphereComponent>(TEXT("HealthCollider"));
	HealthCollider->SetupAttachment(RootComponent);
	HealthCollider->InitSphereRadius(25.f);

	AttackCollider = CreateDefaultSubobject<USphereComponent>(TEXT("AttackCollider"));
	AttackCollider->SetupAttachment(RootComponent);
	AttackCollider->InitSphereRadius(60.f);

	/** Movement Component Default Values*/
	MovementComponent = CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>(TEXT("MovementComponent"));
	MovementComponent->UpdatedComponent = Root;
	Cast<UFloatingPawnMovement>(MovementComponent)->MaxSpeed = 2000.f;

	BeeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BeeMesh"));
	BeeMesh->SetupAttachment(RootComponent);


	
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

	if (bOverlapping)
	{
		APawn* Pawn = GetWorld()->GetFirstPlayerController()->GetPawn();
		APlayerCar* Player = Cast<APlayerCar>(Pawn);

		AIController->MoveToActor(Player, 10.f);
		AIController->SetFocus(Player);
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
