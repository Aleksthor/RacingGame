// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "HoverComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RACINGGAME_API UHoverComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHoverComponent();


	UPROPERTY(EditAnywhere, Category = "HoverVariables")
	float TraceLength;

	UPROPERTY(EditAnywhere, Category = "HoverVariables")
	float HoverForce;

	UPROPERTY(EditAnywhere, Category = "HoverVariables")
	float LinearDamping;

	UPROPERTY(EditAnywhere, Category = "HoverVariables")
	float AngularDamping;

	UPROPERTY(EditAnywhere, Category = "HoverVariables")
	FHitResult HitResult;


	float LinearDampingDefault = 5.f;
	float AngularDampingDefault = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HoverVariables")
	class APlayerCar* PlayerCar;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
