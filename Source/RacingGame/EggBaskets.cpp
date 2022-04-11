// Fill out your copyright notice in the Description page of Project Settings.


#include "EggBaskets.h"
#include "Components/SphereComponent.h"
#include "PlayerCar.h"
#include "RacingGameGameModeBase.h"

// Sets default values
AEggBaskets::AEggBaskets()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	SetRootComponent(Collider);

	MagnetCollider = CreateDefaultSubobject<USphereComponent>(TEXT("MagnetCollider"));
	MagnetCollider->SetupAttachment(GetRootComponent());


	EggBasketMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EggBasketMesh"));
	EggBasketMesh->SetupAttachment(Collider);
}

// Called when the game starts or when spawned
void AEggBaskets::BeginPlay()
{
	Super::BeginPlay();

	Collider->OnComponentBeginOverlap.AddDynamic(this, &AEggBaskets::OnOverlap);

	MagnetCollider->OnComponentBeginOverlap.AddDynamic(this, &AEggBaskets::MagnetOnOverlapBegin);
	MagnetCollider->OnComponentEndOverlap.AddDynamic(this, &AEggBaskets::MagnetOnOverlapEnd);
	
	StartLocation = GetActorLocation();
	StartRotation = GetActorRotation();
}

// Called every frame
void AEggBaskets::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ARacingGameGameModeBase* GameModeBase = Cast<ARacingGameGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameModeBase->TimeAttack)
	{
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
		this->Destroy();
	}

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

	AGameModeBase* GameMode = GetWorld()->GetAuthGameMode();
	if (GameMode)
	{
		if (Cast<ARacingGameGameModeBase>(GameMode)->CurrentRound == 2 && !Round2)
		{
			bMagnetPull = false;
			SetActorLocation(StartLocation);
			SetActorRotation(StartRotation);
			SetActorHiddenInGame(false);
			SetActorEnableCollision(true);
			Round2 = true;
		}
		if (Cast<ARacingGameGameModeBase>(GameMode)->CurrentRound == 3 && !Round3)
		{
			bMagnetPull = false;
			SetActorLocation(StartLocation);
			SetActorRotation(StartRotation);
			SetActorHiddenInGame(false);
			SetActorEnableCollision(true);
			Round3 = true;
		}
	}

}

void AEggBaskets::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCar* Player = Cast<APlayerCar>(OtherActor);
	if (Player)
	{
		Player->ReloadEggs(ReloadAmount);
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
	}

}

void AEggBaskets::MagnetOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCar* Player = Cast<APlayerCar>(OtherActor);
	if (Player)
	{
		bMagnetPull = true;
	}
}

void AEggBaskets::MagnetOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
}

