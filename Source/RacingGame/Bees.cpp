// Fill out your copyright notice in the Description page of Project Settings.


#include "Bees.h"
#include "Target.h"
#include "Components/SphereComponent.h"
#include "Sound/SoundCue.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/PawnMovementComponent.h"
#include "PlayerCar.h"
#include "Bomb.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "ObjectiveComponent.h"

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

	Normal = CreateDefaultSubobject<UStaticMesh>(TEXT("Normal"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh1(TEXT("StaticMesh'/Game/Meshes/Enemies/Beezzzzzzz/Bee_big.Bee_big'"));
	Normal = Mesh1.Object;

	Attack = CreateDefaultSubobject<UStaticMesh>(TEXT("Attack"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh2(TEXT("StaticMesh'/Game/Meshes/Enemies/Beezzzzzzz/bee_damaged.bee_damaged'"));
	Attack = Mesh2.Object;
	
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

	FVector ForwardVector = UKismetMathLibrary::GetForwardVector(GetControlRotation());

	if (bGivenDamage)
	{
		bCanGiveDamage = false;
		DamageClock += DeltaTime;

		if (DamageClock > DamageTimer)
		{
			BeeMesh->SetStaticMesh(Normal);
			BeeMesh->SetWorldRotation(ForwardVector.Rotation());
			BeeMesh->SetRelativeScale3D(FVector(2.5f, 2.5f, 2.5f));
			DamageClock = 0.f;
			bCanGiveDamage = true;
			bGivenDamage = false;
		}
	}
	if (bAttacking)
	{
		if (bCanGiveDamage)
		{
			if (OnAttackSound)
			{
				UGameplayStatics::PlaySound2D(this, OnAttackSound);
			}
			BeeMesh->SetStaticMesh(Attack);
			BeeMesh->SetWorldRotation(ForwardVector.Rotation());
			BeeMesh->SetRelativeScale3D(FVector(3.f, 3.f, 3.f));
			APawn* Pawn = GetWorld()->GetFirstPlayerController()->GetPawn();
			APlayerCar* Player = Cast<APlayerCar>(Pawn);
			Player->LoseHealth();
			bGivenDamage = true;
		}
	}


	// There is no bOrientRotationToMovement in FloatingPawnMovement

	ForwardVector *= -1.f;
	BeeMesh->SetWorldRotation(ForwardVector.Rotation());

	if (bOverlapping && !bAttacking)
	{
		APawn* Pawn = GetWorld()->GetFirstPlayerController()->GetPawn();
		APlayerCar* Player = Cast<APlayerCar>(Pawn);

		AIController->MoveToActor(Player, 2.f);
		



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
		
		APlayerCar* Player = Cast<APlayerCar>(GetWorld()->GetFirstPlayerController()->GetPawn());
		if (Player)
		{
			Player->ObjectiveComponent->NoBeesHit = false;
		}
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

