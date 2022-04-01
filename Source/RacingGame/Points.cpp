// Fill out your copyright notice in the Description page of Project Settings.


#include "Points.h"
#include "Components/BoxComponent.h"
#include "PlayerCar.h"

// Sets default values
APoints::APoints()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	SetRootComponent(Collider);
	Collider->OnComponentBeginOverlap.AddDynamic(this, &APoints::OnOverlap);

	PointsMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PointsMesh"));
	PointsMesh->SetupAttachment(Collider);
}

// Called when the game starts or when spawned
void APoints::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APoints::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APoints::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCar* Player = Cast<APlayerCar>(OtherActor);
	if (Player)
	{
		Player->GivePoints(PointsGiven);
		isHit = true;
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);

	}
}

