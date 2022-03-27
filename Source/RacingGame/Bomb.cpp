// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomb.h"
#include "PlayerCar.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SphereComponent.h"

// Sets default values
ABomb::ABomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	SetRootComponent(Collider);
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ABomb::OnOverlap);
	Collider->InitSphereRadius(35.f);
	Collider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Collider->SetSimulatePhysics(true);
	Collider->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);


	BombMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BombMesh"));
	BombMesh->SetupAttachment(Collider);
	

	Force = 100000.f;

}

// Called when the game starts or when spawned
void ABomb::BeginPlay()
{
	Super::BeginPlay();

	APawn* Temp = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (Temp)
	{
		Player = Cast<APlayerCar>(Temp);
	}

	
}

// Called every frame
void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	

	if (Player && !bAddedForce)
	{
		FVector PlayerForwardVector = Player->GetActorForwardVector();
		PlayerForwardVector *= 3.f;

		FVector PlayerUpVector = Player->GetActorUpVector();
		FVector OutputVector;
		if (Player->ShootHigh)
		{
			OutputVector = PlayerForwardVector + PlayerUpVector * 0.4f;
		}
		else
		{
			OutputVector = PlayerForwardVector + PlayerUpVector * 0.10f;
		}
	

		OutputVector.Normalize();

		OutputVector *= Force;

		Collider->AddImpulse(OutputVector);
		TimesAddedForce++;
		if (TimesAddedForce > 2 )
		{
			bAddedForce = true;
		}
		

	}


}

void ABomb::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{



	// Destory if we hit terrain
	if (OtherComponent->GetCollisionProfileName() == FName("BlockAll"))
	{
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
		this->Destroy();
	}


}

void ABomb::DestroyBomb()
{
}

