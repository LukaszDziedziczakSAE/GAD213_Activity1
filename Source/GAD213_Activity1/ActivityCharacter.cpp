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
	
	TargetRotation = GetMesh()->GetRelativeRotation().Euler().Z;
	UE_LOG(LogTemp, Warning, TEXT("StartingRotation=%s"), *GetMesh()->GetRelativeRotation().Euler().ToString());
}

// Called every frame
void AActivityCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Movement.Length() > 0)
	{
		TargetRotation = (FMath::Atan2(-Movement.Y, Movement.X)) * (180 / PI);
		
	}

	float CurrentRoll = GetMesh()->GetRelativeRotation().Euler().Z;

	if (CurrentRoll != TargetRotation)
	{
		float Differance = TargetRotation - CurrentRoll;
		float step = (RotationRate * DeltaTime);
		UE_LOG(LogTemp, Warning, TEXT("CurrentRoll=%f, TargetRotation=%f, Differance=%f"), CurrentRoll, TargetRotation, Differance);

		if (Differance < (step*1.5) && Differance > -(step*1.5))
		{
			GetMesh()->SetRelativeRotation(FRotator::MakeFromEuler(FVector(0, 0, TargetRotation)));
			UE_LOG(LogTemp, Warning, TEXT("Inside Step=%f"), step);
		}
		else
		{
			if ((Differance < 0 && Differance > -180) || Differance > 180)
			{
				float NewRoll = CurrentRoll - step;

				GetMesh()->SetRelativeRotation(FRotator::MakeFromEuler(FVector(0, 0, NewRoll)));
				UE_LOG(LogTemp, Warning, TEXT("NewRoll=%f, Step=%f"), NewRoll, step);
			}
			else
			{
				float NewRoll = CurrentRoll + step;

				GetMesh()->SetRelativeRotation(FRotator::MakeFromEuler(FVector(0, 0, NewRoll)));
				UE_LOG(LogTemp, Warning, TEXT("NewRoll=%f, Step=%f"), NewRoll, step);
			}

			
		}
	}
	
	

	/*if (CurrentRoll > TargetRotation)
	{
		double NewRoll = CurrentRoll + (RotationRate * DeltaTime);
		FRotator NewRotator = FRotator::MakeFromEuler(FVector(0, 0, NewRoll));

		GetMesh()->SetRelativeRotation(NewRotator);
		UE_LOG(LogTemp, Warning, TEXT("NewRotation=%s"), *GetMesh()->GetRelativeRotation().Euler().ToString());
	}
	else if (CurrentRoll < TargetRotation)
	{
		double NewRoll = CurrentRoll + -(RotationRate * DeltaTime);
		FRotator NewRotator = FRotator::MakeFromEuler(FVector(0, 0, NewRoll));

		GetMesh()->SetRelativeRotation(NewRotator);
		UE_LOG(LogTemp, Warning, TEXT("NewRotation=%s"), *GetMesh()->GetRelativeRotation().Euler().ToString());
	}*/
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
