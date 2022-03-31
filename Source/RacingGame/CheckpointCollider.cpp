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
			
			isHit = true;

			AGameModeBase* GameModeBase = GetWorld()->GetAuthGameMode();
			switch (Cast<ARacingGameGameModeBase>(GameModeBase)->CurrentCheckpoint)
			{
			case 0:

				Cast<APlayerCar>(OtherActor)->SectionAggregate = Cast<APlayerCar>(OtherActor)->SectionTimer - Cast<ARacingGameGameModeBase>(GameModeBase)->Section1BestTime;

				switch (Cast<ARacingGameGameModeBase>(GameModeBase)->CurrentRound)
				{
				case 1:
					if (FMath::IsNearlyZero(Cast<ARacingGameGameModeBase>(GameModeBase)->WorldCheckpoint1))
					{
						if (Player)
						{
							Player->FirstRun = true;
						}
					}
					Cast<APlayerCar>(OtherActor)->WorldAggregate = Cast<APlayerCar>(OtherActor)->WorldTimer - Cast<ARacingGameGameModeBase>(GameModeBase)->WorldCheckpoint1;
					Cast<ARacingGameGameModeBase>(GameModeBase)->WorldCheckpoint1 = Cast<APlayerCar>(OtherActor)->WorldTimer;
					break;
				case 2:
					Cast<APlayerCar>(OtherActor)->WorldAggregate = Cast<APlayerCar>(OtherActor)->WorldTimer - Cast<ARacingGameGameModeBase>(GameModeBase)->WorldCheckpoint8;
					Cast<ARacingGameGameModeBase>(GameModeBase)->WorldCheckpoint8 = Cast<APlayerCar>(OtherActor)->WorldTimer;
					
					break;
				case 3:
					Cast<APlayerCar>(OtherActor)->WorldAggregate = Cast<APlayerCar>(OtherActor)->WorldTimer - Cast<ARacingGameGameModeBase>(GameModeBase)->WorldCheckpoint15;
					Cast<ARacingGameGameModeBase>(GameModeBase)->WorldCheckpoint15 = Cast<APlayerCar>(OtherActor)->WorldTimer;
				
					break;
				default:
					break;
				}

				if (FMath::IsNearlyZero(Cast<ARacingGameGameModeBase>(GameModeBase)->Section1BestTime) || Cast<APlayerCar>(OtherActor)->SectionTimer < Cast<ARacingGameGameModeBase>(GameModeBase)->Section1BestTime)
				{
					Cast<ARacingGameGameModeBase>(GameModeBase)->Section1BestTime = Cast<APlayerCar>(OtherActor)->SectionTimer;
				}
				break;

			case 1:

				Cast<APlayerCar>(OtherActor)->SectionAggregate = Cast<APlayerCar>(OtherActor)->SectionTimer - Cast<ARacingGameGameModeBase>(GameModeBase)->Section2BestTime;

				switch (Cast<ARacingGameGameModeBase>(GameModeBase)->CurrentRound)
				{
				case 1:
					Cast<APlayerCar>(OtherActor)->WorldAggregate = Cast<APlayerCar>(OtherActor)->WorldTimer - Cast<ARacingGameGameModeBase>(GameModeBase)->WorldCheckpoint2;
					Cast<ARacingGameGameModeBase>(GameModeBase)->WorldCheckpoint2 = Cast<APlayerCar>(OtherActor)->WorldTimer;
				
					break;
				case 2:	
					Cast<APlayerCar>(OtherActor)->WorldAggregate = Cast<APlayerCar>(OtherActor)->WorldTimer - Cast<ARacingGameGameModeBase>(GameModeBase)->WorldCheckpoint9;
					Cast<ARacingGameGameModeBase>(GameModeBase)->WorldCheckpoint9 = Cast<APlayerCar>(OtherActor)->WorldTimer;
				
					break;
				case 3:
					Cast<APlayerCar>(OtherActor)->WorldAggregate = Cast<APlayerCar>(OtherActor)->WorldTimer - Cast<ARacingGameGameModeBase>(GameModeBase)->WorldCheckpoint16;
					Cast<ARacingGameGameModeBase>(GameModeBase)->WorldCheckpoint16 = Cast<APlayerCar>(OtherActor)->WorldTimer;
					
					break;
				default:
					break;
				}

				if (FMath::IsNearlyZero(Cast<ARacingGameGameModeBase>(GameModeBase)->Section2BestTime) || Cast<APlayerCar>(OtherActor)->SectionTimer < Cast<ARacingGameGameModeBase>(GameModeBase)->Section2BestTime)
				{
					Cast<ARacingGameGameModeBase>(GameModeBase)->Section2BestTime = Cast<APlayerCar>(OtherActor)->SectionTimer;
				}
				break;

			case 2:

				Cast<APlayerCar>(OtherActor)->SectionAggregate = Cast<APlayerCar>(OtherActor)->SectionTimer - Cast<ARacingGameGameModeBase>(GameModeBase)->Section3BestTime;

				switch (Cast<ARacingGameGameModeBase>(GameModeBase)->CurrentRound)
				{
				case 1:
					Cast<APlayerCar>(OtherActor)->WorldAggregate = Cast<APlayerCar>(OtherActor)->WorldTimer - Cast<ARacingGameGameModeBase>(GameModeBase)->WorldCheckpoint3;
					Cast<ARacingGameGameModeBase>(GameModeBase)->WorldCheckpoint3 = Cast<APlayerCar>(OtherActor)->WorldTimer;
					break;
				case 2:
					Cast<APlayerCar>(OtherActor)->WorldAggregate = Cast<APlayerCar>(OtherActor)->WorldTimer - Cast<ARacingGameGameModeBase>(GameModeBase)->WorldCheckpoint10;
					Cast<ARacingGameGameModeBase>(GameModeBase)->WorldCheckpoint10 = Cast<APlayerCar>(OtherActor)->WorldTimer;
					
					break;
				case 3:
					Cast<APlayerCar>(OtherActor)->WorldAggregate = Cast<APlayerCar>(OtherActor)->WorldTimer - Cast<ARacingGameGameModeBase>(GameModeBase)->WorldCheckpoint17;
					Cast<ARacingGameGameModeBase>(GameModeBase)->WorldCheckpoint17 = Cast<APlayerCar>(OtherActor)->WorldTimer;
					
					break;
				default:
					break;
				}

				if (FMath::IsNearlyZero(Cast<ARacingGameGameModeBase>(GameModeBase)->Section3BestTime) || Cast<APlayerCar>(OtherActor)->SectionTimer < Cast<ARacingGameGameModeBase>(GameModeBase)->Section3BestTime)
				{
					Cast<ARacingGameGameModeBase>(GameModeBase)->Section3BestTime = Cast<APlayerCar>(OtherActor)->SectionTimer;
				}
				break;

			case 3:

				Cast<APlayerCar>(OtherActor)->SectionAggregate = Cast<APlayerCar>(OtherActor)->SectionTimer - Cast<ARacingGameGameModeBase>(GameModeBase)->Section4BestTime;

				switch (Cast<ARacingGameGameModeBase>(GameModeBase)->CurrentRound)
				{
				case 1:
					
					Cast<APlayerCar>(OtherActor)->WorldAggregate = Cast<APlayerCar>(OtherActor)->WorldTimer - Cast<ARacingGameGameModeBase>(GameModeBase)->WorldCheckpoint4;
					Cast<ARacingGameGameModeBase>(GameModeBase)->WorldCheckpoint4 = Cast<APlayerCar>(OtherActor)->WorldTimer;
					break;
				case 2:
					
					Cast<APlayerCar>(OtherActor)->WorldAggregate = Cast<APlayerCar>(OtherActor)->WorldTimer - Cast<ARacingGameGameModeBase>(GameModeBase)->WorldCheckpoint11;
					Cast<ARacingGameGameModeBase>(GameModeBase)->WorldCheckpoint11 = Cast<APlayerCar>(OtherActor)->WorldTimer;
					break;
				case 3:
					
					Cast<APlayerCar>(OtherActor)->WorldAggregate = Cast<APlayerCar>(OtherActor)->WorldTimer - Cast<ARacingGameGameModeBase>(GameModeBase)->WorldCheckpoint18;
					Cast<ARacingGameGameModeBase>(GameModeBase)->WorldCheckpoint18 = Cast<APlayerCar>(OtherActor)->WorldTimer;
					break;
				default:
					break;
				}
				if (FMath::IsNearlyZero(Cast<ARacingGameGameModeBase>(GameModeBase)->Section4BestTime) || Cast<APlayerCar>(OtherActor)->SectionTimer < Cast<ARacingGameGameModeBase>(GameModeBase)->Section4BestTime)
				{
					Cast<ARacingGameGameModeBase>(GameModeBase)->Section4BestTime = Cast<APlayerCar>(OtherActor)->SectionTimer;
				}
				break;

			case 4:

				Cast<APlayerCar>(OtherActor)->SectionAggregate = Cast<APlayerCar>(OtherActor)->SectionTimer - Cast<ARacingGameGameModeBase>(GameModeBase)->Section5BestTime;

				switch (Cast<ARacingGameGameModeBase>(GameModeBase)->CurrentRound)
				{
				case 1:
				
					Cast<APlayerCar>(OtherActor)->WorldAggregate = Cast<APlayerCar>(OtherActor)->WorldTimer - Cast<ARacingGameGameModeBase>(GameModeBase)->WorldCheckpoint5;	
					Cast<ARacingGameGameModeBase>(GameModeBase)->WorldCheckpoint5 = Cast<APlayerCar>(OtherActor)->WorldTimer;
					break;
				case 2:
					
					Cast<APlayerCar>(OtherActor)->WorldAggregate = Cast<APlayerCar>(OtherActor)->WorldTimer - Cast<ARacingGameGameModeBase>(GameModeBase)->WorldCheckpoint12;
					Cast<ARacingGameGameModeBase>(GameModeBase)->WorldCheckpoint12 = Cast<APlayerCar>(OtherActor)->WorldTimer;
					break;
				case 3:
					
					Cast<APlayerCar>(OtherActor)->WorldAggregate = Cast<APlayerCar>(OtherActor)->WorldTimer - Cast<ARacingGameGameModeBase>(GameModeBase)->WorldCheckpoint19;
					Cast<ARacingGameGameModeBase>(GameModeBase)->WorldCheckpoint19 = Cast<APlayerCar>(OtherActor)->WorldTimer;
					break;
				default:
					break;
				}
				if (FMath::IsNearlyZero(Cast<ARacingGameGameModeBase>(GameModeBase)->Section5BestTime) || Cast<APlayerCar>(OtherActor)->SectionTimer < Cast<ARacingGameGameModeBase>(GameModeBase)->Section5BestTime)
				{
					Cast<ARacingGameGameModeBase>(GameModeBase)->Section5BestTime = Cast<APlayerCar>(OtherActor)->SectionTimer;
				}
				break;

			case 5:

				Cast<APlayerCar>(OtherActor)->SectionAggregate = Cast<APlayerCar>(OtherActor)->SectionTimer - Cast<ARacingGameGameModeBase>(GameModeBase)->Section6BestTime;

				switch (Cast<ARacingGameGameModeBase>(GameModeBase)->CurrentRound)
				{
				case 1:
					Cast<APlayerCar>(OtherActor)->WorldAggregate = Cast<APlayerCar>(OtherActor)->WorldTimer - Cast<ARacingGameGameModeBase>(GameModeBase)->WorldCheckpoint6;
					Cast<ARacingGameGameModeBase>(GameModeBase)->WorldCheckpoint6 = Cast<APlayerCar>(OtherActor)->WorldTimer;
					break;
				case 2:
	
					Cast<APlayerCar>(OtherActor)->WorldAggregate = Cast<APlayerCar>(OtherActor)->WorldTimer - Cast<ARacingGameGameModeBase>(GameModeBase)->WorldCheckpoint13;
					Cast<ARacingGameGameModeBase>(GameModeBase)->WorldCheckpoint13 = Cast<APlayerCar>(OtherActor)->WorldTimer;
					break;
				case 3:
					
					Cast<APlayerCar>(OtherActor)->WorldAggregate = Cast<APlayerCar>(OtherActor)->WorldTimer - Cast<ARacingGameGameModeBase>(GameModeBase)->WorldCheckpoint20;
					Cast<ARacingGameGameModeBase>(GameModeBase)->WorldCheckpoint20 = Cast<APlayerCar>(OtherActor)->WorldTimer;
					break;
				default:
					break;
				}
				if (FMath::IsNearlyZero(Cast<ARacingGameGameModeBase>(GameModeBase)->Section6BestTime) || Cast<APlayerCar>(OtherActor)->SectionTimer < Cast<ARacingGameGameModeBase>(GameModeBase)->Section6BestTime)
				{
					Cast<ARacingGameGameModeBase>(GameModeBase)->Section6BestTime = Cast<APlayerCar>(OtherActor)->SectionTimer;
				}
				break;

			//case 6:

			//	Cast<APlayerCar>(OtherActor)->SectionAggregate = Cast<APlayerCar>(OtherActor)->SectionTimer - Cast<ARacingGameGameModeBase>(GameModeBase)->Section7BestTime;
			//	
			//	switch (Cast<ARacingGameGameModeBase>(GameModeBase)->CurrentRound)
			//	{
			//	case 1:
			//		Cast<APlayerCar>(OtherActor)->WorldAggregate = Cast<APlayerCar>(OtherActor)->WorldTimer - Cast<ARacingGameGameModeBase>(GameModeBase)->WorldCheckpoint7;
			//		Cast<ARacingGameGameModeBase>(GameModeBase)->WorldCheckpoint7 = Cast<APlayerCar>(OtherActor)->WorldTimer;
			//		break;
			//	case 2:
			//		Cast<APlayerCar>(OtherActor)->WorldAggregate = Cast<APlayerCar>(OtherActor)->WorldTimer - Cast<ARacingGameGameModeBase>(GameModeBase)->WorldCheckpoint14;
			//		Cast<ARacingGameGameModeBase>(GameModeBase)->WorldCheckpoint14 = Cast<APlayerCar>(OtherActor)->WorldTimer;
			//		break;
			//	case 3:
			//		
			//		Cast<APlayerCar>(OtherActor)->WorldAggregate = Cast<APlayerCar>(OtherActor)->WorldTimer - Cast<ARacingGameGameModeBase>(GameModeBase)->WorldCheckpoint21;
			//		Cast<ARacingGameGameModeBase>(GameModeBase)->WorldCheckpoint21 = Cast<APlayerCar>(OtherActor)->WorldTimer;
			//		break;
			//	default:
			//		break;
			//	}
			//	if (FMath::IsNearlyZero(Cast<ARacingGameGameModeBase>(GameModeBase)->Section7BestTime) || Cast<APlayerCar>(OtherActor)->SectionTimer < Cast<ARacingGameGameModeBase>(GameModeBase)->Section7BestTime)
			//	{
			//		Cast<ARacingGameGameModeBase>(GameModeBase)->Section7BestTime = Cast<APlayerCar>(OtherActor)->SectionTimer;
			//	}
			//	break;

			default:
				break;
			}	
			Cast<ARacingGameGameModeBase>(GameModeBase)->CurrentCheckpoint++;
			Cast<APlayerCar>(OtherActor)->SetLastCheckPointTimer();
			Cast<APlayerCar>(OtherActor)->SectionTimer = 0.f;
			Cast<APlayerCar>(OtherActor)->bJustHitCheckPoint = true;
		}
		else
		{
			AGameModeBase* GameModeBase = GetWorld()->GetAuthGameMode();
			Cast<ARacingGameGameModeBase>(GameModeBase)->Reset();
			//Player->bGameOver = true;
		}

	}
}

