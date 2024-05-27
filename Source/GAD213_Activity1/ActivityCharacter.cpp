// Fill out your copyright notice in the Description page of Project Settings.


#include "ActivityCharacter.h"
#include "Math/UnrealMathUtility.h"
#include "MathUtil.h"

// Sets default values
AActivityCharacter::AActivityCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AActivityCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AActivityCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Movement.Length() > 0)
	{
		double rad = FMath::Atan2(-Movement.Y, Movement.X);
		double deg = rad * (180 / PI);
		FRotator newRotation = FRotator::MakeFromEuler(FVector(0, 0, deg));
		GetMesh()->SetRelativeRotation(newRotation);
	}
	
}

// Called to bind functionality to input
void AActivityCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AActivityCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AActivityCharacter::MoveRight);
}

void AActivityCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
	Movement.Y = AxisValue;
}

void AActivityCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
	Movement.X = AxisValue;
}
