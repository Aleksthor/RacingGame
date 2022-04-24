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
	Player = Cast<APlayerCar>(OtherActor);

	if (Player && !isHit)
	{
		if (isValid)
		{
			
			isHit = true;

			AGameModeBase* GameModeBase = GetWorld()->GetAuthGameMode();
			ARacingGameGameModeBase* RacingGameModeBase = Cast<ARacingGameGameModeBase>(GameModeBase);
			


			switch (RacingGameModeBase->CurrentCheckpoint)
			{
			case 0:
				RacingGameModeBase->AddToDeathTimer(10.f);
				Player->CurrentSection = "Section 2";
				Player->SectionAggregate = Player->SectionTimer - RacingGameModeBase->Section1BestTime;
				RacingGameModeBase->CurrentSectionBest = RacingGameModeBase->Section2BestTime;

				switch (RacingGameModeBase->CurrentRound)
				{
				case 1:
					if (FMath::IsNearlyZero(RacingGameModeBase->WorldCheckpoint1))
					{
						if (Player)
						{
							Player->FirstRun = true;
						}
					}
					Player->WorldAggregate = Player->WorldTimer - RacingGameModeBase->WorldCheckpoint1;
					if (RacingGameModeBase->WorldCheckpoint1 > Player->WorldTimer || FMath::IsNearlyZero(RacingGameModeBase->WorldCheckpoint1))
					{
						RacingGameModeBase->WorldCheckpoint1 = Player->WorldTimer;
					}
					RacingGameModeBase->NextBest = RacingGameModeBase->WorldCheckpoint2;
					
					break;
				case 2:
					Player->WorldAggregate = Player->WorldTimer - RacingGameModeBase->WorldCheckpoint8;
					if (RacingGameModeBase->WorldCheckpoint8 > Player->WorldTimer || FMath::IsNearlyZero(RacingGameModeBase->WorldCheckpoint8))
					{
						RacingGameModeBase->WorldCheckpoint8 = Player->WorldTimer;
					}
					RacingGameModeBase->NextBest = RacingGameModeBase->WorldCheckpoint9;
					break;
				case 3:
					Player->WorldAggregate = Player->WorldTimer - RacingGameModeBase->WorldCheckpoint15;
					if (RacingGameModeBase->WorldCheckpoint15 > Player->WorldTimer || FMath::IsNearlyZero(RacingGameModeBase->WorldCheckpoint15))
					{
						RacingGameModeBase->WorldCheckpoint15 = Player->WorldTimer;
					}
					RacingGameModeBase->NextBest = RacingGameModeBase->WorldCheckpoint16;
				
					break;
				default:
					break;
				}

				if (FMath::IsNearlyZero(RacingGameModeBase->Section1BestTime) || Player->SectionTimer < RacingGameModeBase->Section1BestTime)
				{
					RacingGameModeBase->Section1BestTime = Player->SectionTimer;
					RacingGameModeBase->Section1NewBestTime = true;
				}
				break;

			case 1:

				Player->CurrentSection = "Section 3";
				RacingGameModeBase->AddToDeathTimer(15.f);
				Player->SectionAggregate = Player->SectionTimer - RacingGameModeBase->Section2BestTime;
				RacingGameModeBase->CurrentSectionBest = RacingGameModeBase->Section3BestTime;

				switch (RacingGameModeBase->CurrentRound)
				{
				case 1:
					Player->WorldAggregate = Player->WorldTimer - RacingGameModeBase->WorldCheckpoint2;
					if (RacingGameModeBase->WorldCheckpoint2 > Player->WorldTimer || FMath::IsNearlyZero(RacingGameModeBase->WorldCheckpoint2))
					{
						RacingGameModeBase->WorldCheckpoint2 = Player->WorldTimer;
					}
					RacingGameModeBase->NextBest = RacingGameModeBase->WorldCheckpoint3;
					break;
				case 2:	
					Player->WorldAggregate = Player->WorldTimer - RacingGameModeBase->WorldCheckpoint9;
					if (RacingGameModeBase->WorldCheckpoint9 > Player->WorldTimer || FMath::IsNearlyZero(RacingGameModeBase->WorldCheckpoint9))
					{
						RacingGameModeBase->WorldCheckpoint9 = Player->WorldTimer;
					}
					RacingGameModeBase->NextBest = RacingGameModeBase->WorldCheckpoint10;
				
					break;
				case 3:
					Player->WorldAggregate = Player->WorldTimer - RacingGameModeBase->WorldCheckpoint16;
					if (RacingGameModeBase->WorldCheckpoint16 > Player->WorldTimer || FMath::IsNearlyZero(RacingGameModeBase->WorldCheckpoint16))
					{
						RacingGameModeBase->WorldCheckpoint16 = Player->WorldTimer;
					}
					RacingGameModeBase->NextBest = RacingGameModeBase->WorldCheckpoint17;
					break;
				default:
					break;
				}

				if (FMath::IsNearlyZero(RacingGameModeBase->Section2BestTime) || Player->SectionTimer < RacingGameModeBase->Section2BestTime)
				{
					RacingGameModeBase->Section2BestTime = Player->SectionTimer;
					RacingGameModeBase->Section2NewBestTime = true;
				}
				break;

			case 2:
				Player->CurrentSection = "Section 4";
				RacingGameModeBase->AddToDeathTimer(15.f);
				Player->SectionAggregate = Player->SectionTimer - RacingGameModeBase->Section3BestTime;
				RacingGameModeBase->CurrentSectionBest = RacingGameModeBase->Section4BestTime;

				switch (RacingGameModeBase->CurrentRound)
				{
				case 1:
					Player->WorldAggregate = Player->WorldTimer - RacingGameModeBase->WorldCheckpoint3;
					if (RacingGameModeBase->WorldCheckpoint3 > Player->WorldTimer || FMath::IsNearlyZero(RacingGameModeBase->WorldCheckpoint3))
					{
						RacingGameModeBase->WorldCheckpoint3 = Player->WorldTimer;
					}
					RacingGameModeBase->NextBest = RacingGameModeBase->WorldCheckpoint4;
					break;
				case 2:
					Player->WorldAggregate = Player->WorldTimer - RacingGameModeBase->WorldCheckpoint10;
					if (RacingGameModeBase->WorldCheckpoint10 > Player->WorldTimer || FMath::IsNearlyZero(RacingGameModeBase->WorldCheckpoint10))
					{
						RacingGameModeBase->WorldCheckpoint10 = Player->WorldTimer;
					}
					RacingGameModeBase->NextBest = RacingGameModeBase->WorldCheckpoint11;
					break;
				case 3:
					Player->WorldAggregate = Player->WorldTimer - RacingGameModeBase->WorldCheckpoint17;
					if (RacingGameModeBase->WorldCheckpoint17 > Player->WorldTimer || FMath::IsNearlyZero(RacingGameModeBase->WorldCheckpoint17))
					{
						RacingGameModeBase->WorldCheckpoint17 = Player->WorldTimer;
					}
					RacingGameModeBase->NextBest = RacingGameModeBase->WorldCheckpoint18;
					break;
				default:
					break;
				}

				if (FMath::IsNearlyZero(RacingGameModeBase->Section3BestTime) || Player->SectionTimer < RacingGameModeBase->Section3BestTime)
				{
					RacingGameModeBase->Section3BestTime = Player->SectionTimer;
					RacingGameModeBase->Section3NewBestTime = true;
				}
				break;

			case 3:
				Player->CurrentSection = "Section 5";
				RacingGameModeBase->AddToDeathTimer(10.f);
				Player->SectionAggregate = Player->SectionTimer - RacingGameModeBase->Section4BestTime;
				RacingGameModeBase->CurrentSectionBest = RacingGameModeBase->Section5BestTime;

				switch (RacingGameModeBase->CurrentRound)
				{
				case 1:
					
					Player->WorldAggregate = Player->WorldTimer - RacingGameModeBase->WorldCheckpoint4;
					if (RacingGameModeBase->WorldCheckpoint4 > Player->WorldTimer || FMath::IsNearlyZero(RacingGameModeBase->WorldCheckpoint4))
					{
						RacingGameModeBase->WorldCheckpoint4 = Player->WorldTimer;
					}
					RacingGameModeBase->NextBest = RacingGameModeBase->WorldCheckpoint5;
					break;
				case 2:
					
					Player->WorldAggregate = Player->WorldTimer - RacingGameModeBase->WorldCheckpoint11;
					if (RacingGameModeBase->WorldCheckpoint11 > Player->WorldTimer || FMath::IsNearlyZero(RacingGameModeBase->WorldCheckpoint11))
					{
						RacingGameModeBase->WorldCheckpoint11 = Player->WorldTimer;
					}
					RacingGameModeBase->NextBest = RacingGameModeBase->WorldCheckpoint12;
					break;
				case 3:
					
					Player->WorldAggregate = Player->WorldTimer - RacingGameModeBase->WorldCheckpoint18;
					if (RacingGameModeBase->WorldCheckpoint18 > Player->WorldTimer || FMath::IsNearlyZero(RacingGameModeBase->WorldCheckpoint18))
					{
						RacingGameModeBase->WorldCheckpoint18 = Player->WorldTimer;
					}
					RacingGameModeBase->NextBest = RacingGameModeBase->WorldCheckpoint19;
					break;
				default:
					break;
				}
				if (FMath::IsNearlyZero(RacingGameModeBase->Section4BestTime) || Player->SectionTimer < RacingGameModeBase->Section4BestTime)
				{
					RacingGameModeBase->Section4BestTime = Player->SectionTimer;
					RacingGameModeBase->Section4NewBestTime = true;
				}
				break;

			case 4:
				Player->CurrentSection = "Section 6";
				RacingGameModeBase->AddToDeathTimer(10.f);
				Player->SectionAggregate = Player->SectionTimer - RacingGameModeBase->Section5BestTime;
				RacingGameModeBase->CurrentSectionBest = RacingGameModeBase->Section6BestTime;

				switch (RacingGameModeBase->CurrentRound)
				{
				case 1:
				
					Player->WorldAggregate = Player->WorldTimer - RacingGameModeBase->WorldCheckpoint5;
					if (RacingGameModeBase->WorldCheckpoint5 > Player->WorldTimer || FMath::IsNearlyZero(RacingGameModeBase->WorldCheckpoint5))
					{
						RacingGameModeBase->WorldCheckpoint5 = Player->WorldTimer;
					}
					RacingGameModeBase->NextBest = RacingGameModeBase->WorldCheckpoint5;
					break;
				case 2:
					
					Player->WorldAggregate = Player->WorldTimer - RacingGameModeBase->WorldCheckpoint12;
					if (RacingGameModeBase->WorldCheckpoint12 > Player->WorldTimer || FMath::IsNearlyZero(RacingGameModeBase->WorldCheckpoint12))
					{
						RacingGameModeBase->WorldCheckpoint12 = Player->WorldTimer;
					}
					RacingGameModeBase->NextBest = RacingGameModeBase->WorldCheckpoint13;
					break;
				case 3:
					
					Player->WorldAggregate = Player->WorldTimer - RacingGameModeBase->WorldCheckpoint19;

					if (RacingGameModeBase->WorldCheckpoint19 > Player->WorldTimer || FMath::IsNearlyZero(RacingGameModeBase->WorldCheckpoint19))
					{
						RacingGameModeBase->WorldCheckpoint19 = Player->WorldTimer;
					}
					RacingGameModeBase->NextBest = RacingGameModeBase->WorldCheckpoint20;
					break;
				default:
					break;
				}
				if (FMath::IsNearlyZero(RacingGameModeBase->Section5BestTime) || Player->SectionTimer < RacingGameModeBase->Section5BestTime)
				{
					RacingGameModeBase->Section5BestTime = Player->SectionTimer;
					RacingGameModeBase->Section5NewBestTime = true;
				}
				break;

			case 5:
				Player->CurrentSection = "Section 1";
				RacingGameModeBase->AddToDeathTimer(15.f);
				Player->SectionAggregate = Player->SectionTimer - RacingGameModeBase->Section6BestTime;
				RacingGameModeBase->CurrentSectionBest = RacingGameModeBase->Section1BestTime;

				switch (RacingGameModeBase->CurrentRound)
				{
				case 1:
					Player->WorldAggregate = Player->WorldTimer - RacingGameModeBase->WorldCheckpoint6;
					if (RacingGameModeBase->WorldCheckpoint6 > Player->WorldTimer || FMath::IsNearlyZero(RacingGameModeBase->WorldCheckpoint6))
					{
						RacingGameModeBase->WorldCheckpoint6 = Player->WorldTimer;
					}
					RacingGameModeBase->NextBest = RacingGameModeBase->WorldCheckpoint8;
					break;
				case 2:
	
					Player->WorldAggregate = Player->WorldTimer - RacingGameModeBase->WorldCheckpoint13;
					if (RacingGameModeBase->WorldCheckpoint13 > Player->WorldTimer || FMath::IsNearlyZero(RacingGameModeBase->WorldCheckpoint13))
					{
						RacingGameModeBase->WorldCheckpoint13 = Player->WorldTimer;
					}
					RacingGameModeBase->NextBest = RacingGameModeBase->WorldCheckpoint15;
					break;
				case 3:
					
					Player->WorldAggregate = Player->WorldTimer - RacingGameModeBase->WorldCheckpoint20;
					if (RacingGameModeBase->WorldCheckpoint20 > Player->WorldTimer || FMath::IsNearlyZero(RacingGameModeBase->WorldCheckpoint20))
					{
						RacingGameModeBase->WorldCheckpoint20 = Player->WorldTimer;
					}
					break;
				default:
					break;
				}
				if (FMath::IsNearlyZero(RacingGameModeBase->Section6BestTime) || Player->SectionTimer < RacingGameModeBase->Section6BestTime)
				{
					RacingGameModeBase->Section6BestTime = Player->SectionTimer;
					RacingGameModeBase->Section6NewBestTime = true;
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

