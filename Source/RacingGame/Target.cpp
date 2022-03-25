// Fill out your copyright notice in the Description page of Project Settings.


#include "Target.h"
#include "Components/SphereComponent.h"
#include "Bomb.h"
#include "PlayerCar.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
ATarget::ATarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	SetRootComponent(Collider);
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ATarget::OnOverlap);
	Collider->InitSphereRadius(100.f);


	TargetMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BombMesh"));
	TargetMesh->SetupAttachment(Collider);

	PointsGiven = 100;
	SpeedGiven = 300.f;

}

// Called when the game starts or when spawned
void ATarget::BeginPlay()
{
	Super::BeginPlay();
	

	APawn* Temp = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (Temp)
	{
		Player = Cast<APlayerCar>(Temp);
	}
}

// Called every frame
void ATarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATarget::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor->IsA<ABomb>())
	{
		
		Player->GivePoints(PointsGiven);
		Player->bSpeedBoost = true;

		// Raise Movement Speed by 300
		UPawnMovementComponent* Movement = Player->GetMovementComponent();
		Player->SpeedBoostSpeed = Cast<UFloatingPawnMovement>(Movement)->MaxSpeed + SpeedGiven;
		
		// Just a dafety mesure so both object gets destroyed
		Cast<ABomb>(OtherActor)->DestroyBomb();
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
		this->Destroy();

	}

}

void ATarget::DestroyTarget()
{
}

