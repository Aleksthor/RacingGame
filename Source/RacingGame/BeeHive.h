// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BeeHive.generated.h"

class ABees;

UCLASS()
class RACINGGAME_API ABeeHive : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABeeHive();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeeHiveVariables")
	class UBoxComponent* Collider{ nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeeHiveVariables")
	class USphereComponent* SpawnLocationComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeeHiveVariables")
	class UStaticMeshComponent* BeehiveMesh{ nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeeHiveVariables")
	TSubclassOf<ABees> BeesBP;

	TArray<class ABees*> BeeArray;
	ABees* tempBee;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeeHiveVariables")
	class USoundCue* OnHitSound{ nullptr };


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeeHiveVariables")
	FVector SpawnLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeeHiveVariables")
	int NumberOfBees = 2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeeHiveVariables")
	bool bIsHit = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);

};
