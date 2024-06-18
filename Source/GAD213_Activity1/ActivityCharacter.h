// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharactersScanner.h"
#include "ActivityCharacter.generated.h"

UCLASS()
class GAD213_ACTIVITY1_API AActivityCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AActivityCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void MoveForward(float AxisValue);

	UFUNCTION()
	void MoveRight(float AxisValue);

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FVector Movement;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	float TargetRotation;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float RotationRate;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UCharactersScanner* CharactersScanner;

	UFUNCTION()
	void ScanButtonPress();
};
