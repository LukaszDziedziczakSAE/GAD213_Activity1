// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "HealthComponent.h"
#include "Wildlife.generated.h"

UENUM()
enum EType
{
	Herbivore,
	Carnivore
};

UCLASS()
class GAD213_ACTIVITY1_API AWildlife : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWildlife();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TEnumAsByte<EType> Type;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UHealthComponent* Health;

	/** Will either attack or run away, when they see the player character */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	bool ReactOnSight;
};
