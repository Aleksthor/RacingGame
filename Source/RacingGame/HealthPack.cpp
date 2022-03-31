// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPack.h"
#include "Components/BoxComponent.h"
#include "PlayerCar.h"


// Sets default values
AHealthPack::AHealthPack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	SetRootComponent(Collider);
	

	HealthPackMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpeedBoostMesh"));
	HealthPackMesh->SetupAttachment(Collider);
	HealthPackMesh->SetHiddenInGame(false);
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

	if (!Init)
	{
		InitClock += DeltaTime;
		if (InitClock > InitTimer)
		{
			Collider->OnComponentBeginOverlap.AddDynamic(this, &AHealthPack::OnOverlap);
			Init = true;
		}


	}
	


}

void AHealthPack::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCar* Player = Cast<APlayerCar>(OtherActor);
	if (Player)
	{
		Player->Lives++;

		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
		this->Destroy();
	}
}

