// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedBoosterv1.h"
#include "Components/BoxComponent.h"
#include "PlayerCar.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
ASpeedBoosterv1::ASpeedBoosterv1()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	SetRootComponent(Collider);
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ASpeedBoosterv1::OnOverlap);

	SpeedBoostMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpeedBoostMesh"));
	SpeedBoostMesh->SetupAttachment(Collider);
}

// Called when the game starts or when spawned
void ASpeedBoosterv1::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpeedBoosterv1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ASpeedBoosterv1::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCar* Player = Cast<APlayerCar>(OtherActor);
	if (Player)
	{
		Player->bSpeedBoost = true;
		UPawnMovementComponent * Movement = Player->GetMovementComponent();
		Player->SpeedBoostSpeed = Cast<UFloatingPawnMovement>(Movement)->MaxSpeed + SpeedGiven;
		Player->SpeedBoostTimer = Timer;
	}
}