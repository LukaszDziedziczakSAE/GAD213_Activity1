// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Projectile.h"
#include "Firearm.generated.h"

UCLASS()
class GAD213_ACTIVITY1_API AFirearm : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFirearm();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USceneComponent* RootComp;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USceneComponent* Muzzle;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<AProjectile> ProjectilePrefab;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float FireRate;

	UFUNCTION()
	bool CanFire();

	UFUNCTION()
	void Fire(FRotator MuzzleRotation);

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	float LastFireTime;

	UFUNCTION()
	FVector GetMuzzleLocation();
};
