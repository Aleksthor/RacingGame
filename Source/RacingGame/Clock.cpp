// Fill out your copyright notice in the Description page of Project Settings.


#include "Clock.h"
#include "Components/SphereComponent.h"
#include "PlayerCar.h"
#include "RacingGameGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

// Sets default values
AClock::AClock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	SetRootComponent(Collider);

	MagnetCollider = CreateDefaultSubobject<USphereComponent>(TEXT("MagnetCollider"));
	MagnetCollider->SetupAttachment(GetRootComponent());

	ClockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ClockMesh"));
	ClockMesh->SetupAttachment(Collider);
}

// Called when the game starts or when spawned
void AClock::BeginPlay()
{
	Super::BeginPlay();
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AClock::OnOverlap);

	MagnetCollider->OnComponentBeginOverlap.AddDynamic(this, &AClock::MagnetOnOverlapBegin);
	MagnetCollider->OnComponentEndOverlap.AddDynamic(this, &AClock::MagnetOnOverlapEnd);



	StartLocation = GetActorLocation();
	StartRotation = GetActorRotation();

	GameModeBase = Cast<ARacingGameGameModeBase>(GetWorld()->GetAuthGameMode());
}

// Called every frame
void AClock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bMagnetPull)
	{
		APlayerCar* PlayerCar = Cast<APlayerCar>(GetWorld()->GetFirstPlayerController()->GetPawn());
		if (PlayerCar)
		{
			InterSpeed = FMath::FInterpTo(InterSpeed, 25.f, DeltaTime, 5.f);
			FVector InterpLocation = FMath::VInterpTo(GetActorLocation(), PlayerCar->GetActorLocation(), DeltaTime, InterSpeed);
			SetActorLocation(InterpLocation);
		}

	}

	if (GameModeBase)
	{
		if (GameModeBase->CurrentRound == 2 && !Round2)
		{
			bMagnetPull = false;
			SetActorLocation(StartLocation);
			SetActorRotation(StartRotation);
			SetActorHiddenInGame(false);
			SetActorEnableCollision(true);
			Round2 = true;
		}
		if (GameModeBase->CurrentRound == 3 && !Round3)
		{
			bMagnetPull = false;
			SetActorLocation(StartLocation);
			SetActorRotation(StartRotation);
			SetActorHiddenInGame(false);
			SetActorEnableCollision(true);
			Round3 = true;
		}

		if (GameModeBase->ShooterMode)
		{
			SetActorHiddenInGame(true);
			SetActorEnableCollision(false);
			this->Destroy();
		}

	}

	FRotator ActorRotation = GetActorRotation();
	ActorRotation.Yaw += 1.f;
	SetActorRotation(ActorRotation);
}

void AClock::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCar* Player = Cast<APlayerCar>(OtherActor);
	if (Player)
	{
		if (OnHitSound1)
		{
			UGameplayStatics::PlaySound2D(this, OnHitSound1);
		}

		GameModeBase->AddToDeathTimer(TimeGiven);
		isHit = true;
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);

	}
}

void AClock::MagnetOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCar* Player = Cast<APlayerCar>(OtherActor);
	if (Player)
	{
		bMagnetPull = true;
	}
}

void AClock::MagnetOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
}

