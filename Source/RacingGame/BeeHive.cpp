// Fill out your copyright notice in the Description page of Project Settings.


#include "BeeHive.h"
#include "Bees.h"
#include "Bomb.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "RacingGameGameModeBase.h"

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

	BeehiveMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BeehiveMesh"));
	BeehiveMesh->SetupAttachment(GetRootComponent());
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Game/Meshes/Beehive/Beehive.Beehive'"));
	BeehiveMesh->SetStaticMesh(Mesh.Object);
	BeehiveMesh->SetRelativeScale3D(FVector(10.f, 10.f, 10.f));
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
	
	ARacingGameGameModeBase* GameMode = Cast<ARacingGameGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		if (GameMode->ShooterMode)
		{
			if (BeeArray.Num() < NumberOfBees && !bIsHit)
			{
				SpawnClock += DeltaTime;
				if (SpawnClock > SpawnTimer)
				{
					UWorld* World = GetWorld();
					if (World)
					{
						FVector Centre = SpawnLocation;

						float RandX = FMath::FRandRange(Centre.X - 300.f, Centre.X + 300.f);
						float RandY = FMath::FRandRange(Centre.Y - 300.f, Centre.Y + 300.f);
						FVector Location = FVector(RandX, RandY, SpawnLocation.Z);

						tempBee = World->SpawnActor<ABees>(BeesBP, Location, FRotator::ZeroRotator);
						SpawnClock = 0.f;
						BeeArray.Add(tempBee);
					}
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
	}


}

void ABeeHive::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABomb* Bomb = Cast<ABomb>(OtherActor);
	if (Bomb)
	{
		if (OnHitSound)
		{
			UGameplayStatics::PlaySound2D(this, OnHitSound);
		}
		bIsHit = true;

	}

}

