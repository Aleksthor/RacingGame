// Fill out your copyright notice in the Description page of Project Settings.


#include "Target.h"
#include "Components/SphereComponent.h"
#include "Bomb.h"
#include "PlayerCar.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

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

	RedMesh = CreateDefaultSubobject<UStaticMesh>(TEXT("RedMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh1(TEXT("StaticMesh'/Game/Meshes/Items/Baloons/BalloonBlue.BalloonBlue'"));
	RedMesh = Mesh1.Object;

	BlueMesh = CreateDefaultSubobject<UStaticMesh>(TEXT("BlueMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh2(TEXT("StaticMesh'/Game/Meshes/Items/Baloons/BalloonRed.BalloonRed'"));
	BlueMesh = Mesh2.Object;

	YellowMesh = CreateDefaultSubobject<UStaticMesh>(TEXT("YellowMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh3(TEXT("StaticMesh'/Game/Meshes/Items/Baloons/BalloonYellow.BalloonYellow'"));
	YellowMesh = Mesh3.Object;



	PointsGiven = 100;
	SpeedGiven = 300.f;

}

// Called when the game starts or when spawned
void ATarget::BeginPlay()
{
	Super::BeginPlay();

	int Random = FMath::RandRange(1, 3);
	switch (Random)
	{
	case 1:
		TargetMesh->SetStaticMesh(RedMesh);
		break;
	case 2:
		TargetMesh->SetStaticMesh(BlueMesh);
		break;
	case 3:
		TargetMesh->SetStaticMesh(YellowMesh);
		break;
	default:
		break;
	}


	Top = GetActorLocation();
	Top.Z += 60.f;

	Bottom = GetActorLocation();
	Bottom.Z -= 60.f;

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

	FRotator ActorRotation = GetActorRotation();
	ActorRotation.Yaw += RotationSpeed;
	SetActorRotation(ActorRotation);


	if (GoingUp)
	{
		FVector SetVector = FMath::VInterpTo(GetActorLocation(), Top, DeltaTime, 1.5f);
		SetActorLocation(SetVector);

		if (FMath::IsNearlyEqual(SetVector.Z, Top.Z,5.f))
		{
			GoingUp = false;
		}
	}
	if (!GoingUp)
	{
		FVector SetVector = FMath::VInterpTo(GetActorLocation(), Bottom, DeltaTime, 1.5f);
		SetActorLocation(SetVector);

		if (FMath::IsNearlyEqual(SetVector.Z, Bottom.Z, 5.f))
		{
			GoingUp = true;
		}
	}


}

void ATarget::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor->IsA<ABomb>())
	{
		if (OnHitSound)
		{
			UGameplayStatics::PlaySound2D(this, OnHitSound);
		}
		if (Player)
		{	
		Player->GivePoints(PointsGiven);
		Player->bSpeedBoost = true;
		Player->SpeedBoostTimer += SpeedboostTimer;

		// Raise Movement Speed by 300
		UPawnMovementComponent* Movement = Player->GetMovementComponent();
		Player->SpeedBoostSpeed = Player->SpeedBoostSpeed + SpeedGiven;

		}
	
		isHit = true;
		// Just a dafety mesure so both object gets destroyed
		Cast<ABomb>(OtherActor)->DestroyBomb();
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
		

	}

}

void ATarget::DestroyTarget()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	

}

