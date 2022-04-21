// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedBoosterv1.h"
#include "Components/SphereComponent.h"
#include "PlayerCar.h"

#include "GameFramework/FloatingPawnMovement.h"
#include "RacingGameGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

// Sets default values
ASpeedBoosterv1::ASpeedBoosterv1()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	SetRootComponent(Collider);

	MagnetCollider = CreateDefaultSubobject<USphereComponent>(TEXT("MagnetCollider"));
	MagnetCollider->SetupAttachment(GetRootComponent());


	SpeedBoostMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpeedBoostMesh"));
	SpeedBoostMesh->SetupAttachment(Collider);
}

// Called when the game starts or when spawned
void ASpeedBoosterv1::BeginPlay()
{
	Super::BeginPlay();
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ASpeedBoosterv1::OnOverlap);

	MagnetCollider->OnComponentBeginOverlap.AddDynamic(this, &ASpeedBoosterv1::MagnetOnOverlapBegin);
	MagnetCollider->OnComponentEndOverlap.AddDynamic(this, &ASpeedBoosterv1::MagnetOnOverlapEnd);

	ARacingGameGameModeBase* GameMode = Cast<ARacingGameGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		if (GameMode->TimeAttack)
		{
			Timer = 6.f;
			SpeedGiven = 600.f;
		}
	}
	StartLocation = GetActorLocation();
	StartRotation = GetActorRotation();
}

// Called every frame
void ASpeedBoosterv1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bMagnetPull)
	{
		APlayerCar* PlayerCar = Cast<APlayerCar>(GetWorld()->GetFirstPlayerController()->GetPawn());
		if (PlayerCar)
		{
			InterSpeed = FMath::FInterpTo(InterSpeed, 35.f, DeltaTime, 5.f);
			FVector InterpLocation = FMath::VInterpTo(GetActorLocation(), PlayerCar->GetActorLocation(), DeltaTime, InterSpeed);
			SetActorLocation(InterpLocation);
		}

	}

}


void ASpeedBoosterv1::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCar* Player = Cast<APlayerCar>(OtherActor);
	if (Player)
	{
		if (OnHitSound)
		{
			UGameplayStatics::PlaySound2D(this, OnHitSound);
		}
		Player->bSpeedBoost = true;
		Player->SpeedBoostTimer += Timer;

		UPawnMovementComponent* Movement = Player->GetMovementComponent();
		Player->SpeedBoostSpeed = Player->SpeedBoostSpeed + SpeedGiven;
		isHit = true;
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
		
	}
}

void ASpeedBoosterv1::MagnetOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCar* Player = Cast<APlayerCar>(OtherActor);
	if (Player)
	{
		bMagnetPull = true;
	}
}

void ASpeedBoosterv1::MagnetOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{

}
