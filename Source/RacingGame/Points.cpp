// Fill out your copyright notice in the Description page of Project Settings.


#include "Points.h"
#include "Components/SphereComponent.h"
#include "PlayerCar.h"
#include "RacingGameGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

// Sets default values
APoints::APoints()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	SetRootComponent(Collider);

	MagnetCollider = CreateDefaultSubobject<USphereComponent>(TEXT("MagnetCollider"));
	MagnetCollider->SetupAttachment(GetRootComponent());

	PointsMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PointsMesh"));
	PointsMesh->SetupAttachment(Collider);
}

// Called when the game starts or when spawned
void APoints::BeginPlay()
{
	Super::BeginPlay();
	
	Collider->OnComponentBeginOverlap.AddDynamic(this, &APoints::OnOverlap);

	MagnetCollider->OnComponentBeginOverlap.AddDynamic(this, &APoints::MagnetOnOverlapBegin);
	MagnetCollider->OnComponentEndOverlap.AddDynamic(this, &APoints::MagnetOnOverlapEnd);



	StartLocation = GetActorLocation();
	StartRotation = GetActorRotation();

	GameModeBase = Cast<ARacingGameGameModeBase>(GetWorld()->GetAuthGameMode());
}

// Called every frame
void APoints::Tick(float DeltaTime)
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

		if (GameModeBase->TimeAttack)
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

void APoints::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCar* Player = Cast<APlayerCar>(OtherActor);
	if (Player)
	{
		int Random = FMath::RandRange(1, 2);
		if (Random == 1)
		{
			if (OnHitSound1)
			{
				UGameplayStatics::PlaySound2D(this, OnHitSound1);
			}
		}
		else
		{
			if (OnHitSound2)
			{
				UGameplayStatics::PlaySound2D(this, OnHitSound2);
			}
		}
		Player->GivePoints(PointsGiven);
		isHit = true;
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);

	}
}

void APoints::MagnetOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCar* Player = Cast<APlayerCar>(OtherActor);
	if (Player)
	{
		bMagnetPull = true;
	}
}

void APoints::MagnetOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{

}

