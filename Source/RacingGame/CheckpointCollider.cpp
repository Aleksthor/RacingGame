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
			
			isHit = true;

			AGameModeBase* GameModeBase = GetWorld()->GetAuthGameMode();
			switch (Cast<ARacingGameGameModeBase>(GameModeBase)->CurrentCheckpoint)
			{
			case 0:
				if (FMath::IsNearlyZero(Cast<ARacingGameGameModeBase>(GameModeBase)->Section1BestTime) || Cast<APlayerCar>(OtherActor)->SectionTimer < Cast<ARacingGameGameModeBase>(GameModeBase)->Section1BestTime)
				{
					Cast<ARacingGameGameModeBase>(GameModeBase)->Section1BestTime = Cast<APlayerCar>(OtherActor)->SectionTimer;
				}
				break;
			case 1:
				if (FMath::IsNearlyZero(Cast<ARacingGameGameModeBase>(GameModeBase)->Section2BestTime) || Cast<APlayerCar>(OtherActor)->SectionTimer < Cast<ARacingGameGameModeBase>(GameModeBase)->Section2BestTime)
				{
					Cast<ARacingGameGameModeBase>(GameModeBase)->Section2BestTime = Cast<APlayerCar>(OtherActor)->SectionTimer;
				}
				break;
			case 2:
				if (FMath::IsNearlyZero(Cast<ARacingGameGameModeBase>(GameModeBase)->Section3BestTime) || Cast<APlayerCar>(OtherActor)->SectionTimer < Cast<ARacingGameGameModeBase>(GameModeBase)->Section3BestTime)
				{
					Cast<ARacingGameGameModeBase>(GameModeBase)->Section3BestTime = Cast<APlayerCar>(OtherActor)->SectionTimer;
				}
				break;
			case 3:
				if (FMath::IsNearlyZero(Cast<ARacingGameGameModeBase>(GameModeBase)->Section4BestTime) || Cast<APlayerCar>(OtherActor)->SectionTimer < Cast<ARacingGameGameModeBase>(GameModeBase)->Section4BestTime)
				{
					Cast<ARacingGameGameModeBase>(GameModeBase)->Section4BestTime = Cast<APlayerCar>(OtherActor)->SectionTimer;
				}
				break;
			case 4:
				if (FMath::IsNearlyZero(Cast<ARacingGameGameModeBase>(GameModeBase)->Section5BestTime) || Cast<APlayerCar>(OtherActor)->SectionTimer < Cast<ARacingGameGameModeBase>(GameModeBase)->Section5BestTime)
				{
					Cast<ARacingGameGameModeBase>(GameModeBase)->Section5BestTime = Cast<APlayerCar>(OtherActor)->SectionTimer;
				}
				break;
			case 5:
				if (FMath::IsNearlyZero(Cast<ARacingGameGameModeBase>(GameModeBase)->Section6BestTime) || Cast<APlayerCar>(OtherActor)->SectionTimer < Cast<ARacingGameGameModeBase>(GameModeBase)->Section6BestTime)
				{
					Cast<ARacingGameGameModeBase>(GameModeBase)->Section6BestTime = Cast<APlayerCar>(OtherActor)->SectionTimer;
				}
				break;
			case 6:
				if (FMath::IsNearlyZero(Cast<ARacingGameGameModeBase>(GameModeBase)->Section7BestTime) || Cast<APlayerCar>(OtherActor)->SectionTimer < Cast<ARacingGameGameModeBase>(GameModeBase)->Section7BestTime)
				{
					Cast<ARacingGameGameModeBase>(GameModeBase)->Section7BestTime = Cast<APlayerCar>(OtherActor)->SectionTimer;
				}
				break;
			default:
				break;
			}	
			Cast<APlayerCar>(OtherActor)->SectionTimer = 0.f;
			Cast<ARacingGameGameModeBase>(GameModeBase)->CurrentCheckpoint++;
		}
		else
		{
			AGameModeBase* GameModeBase = GetWorld()->GetAuthGameMode();
			Cast<ARacingGameGameModeBase>(GameModeBase)->Reset();
			//Player->bGameOver = true;
		}

	}
}

