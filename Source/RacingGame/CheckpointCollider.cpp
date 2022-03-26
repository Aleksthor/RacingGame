// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckpointCollider.h"
#include "Components/BoxComponent.h"
#include "PlayerCar.h"
#include "RacingGameGameModeBase.h"

// Sets default values
ACheckpointCollider::ACheckpointCollider()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	SetRootComponent(Collider);
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ACheckpointCollider::OnOverlap);
	Collider->SetBoxExtent(FVector(2000.f, 50.f, 500.f));
}

// Called when the game starts or when spawned
void ACheckpointCollider::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACheckpointCollider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACheckpointCollider::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{


	if (OtherActor->IsA<APlayerCar>() && !isHit)
	{
		if (isValid)
		{
			Cast<APlayerCar>(OtherActor)->SetLastCheckPointTimer();
			Cast<APlayerCar>(OtherActor)->bJustHitCheckPoint = true;
			Cast<APlayerCar>(OtherActor)->SectionTimer = 0.f;
			isHit = true;

			AGameModeBase* GameModeBase = GetWorld()->GetAuthGameMode();
			Cast<ARacingGameGameModeBase>(GameModeBase)->CurrentCheckpoint++;
		}
		else
		{
			AGameModeBase* GameModeBase = GetWorld()->GetAuthGameMode();
			Cast<ARacingGameGameModeBase>(GameModeBase)->Reset();
		}

	}
}

