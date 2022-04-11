// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPack.h"
#include "Components/SphereComponent.h"
#include "PlayerCar.h"


// Sets default values
AHealthPack::AHealthPack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	SetRootComponent(Collider);
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AHealthPack::OnOverlap);
	
	MagnetCollider = CreateDefaultSubobject<USphereComponent>(TEXT("MagnetCollider"));
	MagnetCollider->SetupAttachment(GetRootComponent());

	MagnetCollider->OnComponentBeginOverlap.AddDynamic(this, &AHealthPack::MagnetOnOverlapBegin);
	MagnetCollider->OnComponentEndOverlap.AddDynamic(this, &AHealthPack::MagnetOnOverlapEnd);

	HealthPackMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpeedBoostMesh"));
	HealthPackMesh->SetupAttachment(GetRootComponent());
	HealthPackMesh->SetHiddenInGame(true);
}

// Called when the game starts or when spawned
void AHealthPack::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AHealthPack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bMagnetPull && Init)
	{
		APlayerCar* PlayerCar = Cast<APlayerCar>(GetWorld()->GetFirstPlayerController()->GetPawn());
		if (PlayerCar)
		{
			InterSpeed = FMath::FInterpTo(InterSpeed, 25.f, DeltaTime, 5.f);
			FVector InterpLocation = FMath::VInterpTo(GetActorLocation(), PlayerCar->GetActorLocation(), DeltaTime, InterSpeed);
			SetActorLocation(InterpLocation);
		}
		
	}

	if (!Init)
	{
		InitClock += DeltaTime;
		if (InitClock > InitTimer)
		{
			HealthPackMesh->SetHiddenInGame(false);
			Init = true;
		}


	}

	FRotator ActorRotation = GetActorRotation();
	ActorRotation.Yaw += 1.f;
	SetActorRotation(ActorRotation);
	


}

void AHealthPack::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCar* Player = Cast<APlayerCar>(OtherActor);
	if (Player && Init)
	{
		Player->Lives++;

		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
		this->Destroy();
	}
}

void AHealthPack::MagnetOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCar* Player = Cast<APlayerCar>(OtherActor);
	if (Player)
	{
		bMagnetPull = true;
	}
}

void AHealthPack::MagnetOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{

}

