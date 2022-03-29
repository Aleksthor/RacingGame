// Fill out your copyright notice in the Description page of Project Settings.


#include "BeeHive.h"
#include "Bees.h"
#include "Bomb.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ABeeHive::ABeeHive()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	SetRootComponent(Collider);

	SpawnLocationComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SpawnLocationComponent"));
	SpawnLocationComponent->SetupAttachment(Collider);
	SpawnLocationComponent->InitSphereRadius(100.f);
}

// Called when the game starts or when spawned
void ABeeHive::BeginPlay()
{
	Super::BeginPlay();
	
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ABeeHive::OnOverlap);

	SpawnLocation = SpawnLocationComponent->GetComponentLocation();
}

// Called every frame
void ABeeHive::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (BeeArray.Num() < NumberOfBees && bIsHit)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			FVector Centre = SpawnLocation;

			float RandX = FMath::FRandRange(Centre.X - 300.f, Centre.X + 300.f);
			float RandY = FMath::FRandRange(Centre.Y - 300.f, Centre.Y + 300.f);
			FVector Location = FVector(RandX, RandY, SpawnLocation.Z);

			tempBee = World->SpawnActor<ABees>(BeesBP, Location, FRotator::ZeroRotator);
			BeeArray.Add(tempBee);
		}
	}
	for (int i{}; i < BeeArray.Num(); i++)
	{
		if (BeeArray[i]->bDead)
		{
			BeeArray[i]->Destroy();
			BeeArray.RemoveAt(i);
		}
	}
}

void ABeeHive::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABomb* Bomb = Cast<ABomb>(OtherActor);
	if (Bomb)
	{
		bIsHit = true;

	}

}

