// Fill out your copyright notice in the Description page of Project Settings.


#include "RacingEnemy.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerCar.h"

// Sets default values
ARacingEnemy::ARacingEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARacingEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void ARacingEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

}

// Called to bind functionality to input
void ARacingEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

