// Fill out your copyright notice in the Description page of Project Settings.


#include "ActivityCharacter.h"
#include "Math/UnrealMathUtility.h"
#include "MathUtil.h"

// Sets default values
AActivityCharacter::AActivityCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CharactersScanner = CreateDefaultSubobject<UCharactersScanner>(TEXT("Characters Scanner"));
}

// Called when the game starts or when spawned
void AActivityCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	TargetRotation = GetMesh()->GetRelativeRotation().Euler().Z;
	//UE_LOG(LogTemp, Warning, TEXT("StartingRotation=%s"), *GetMesh()->GetRelativeRotation().Euler().ToString());
}

// Called every frame
void AActivityCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Movement.Length() > 0) // if we are recieving input from player
	{
		// determin rotation based on input from player
		TargetRotation = (FMath::Atan2(-Movement.Y, Movement.X)) * (180 / PI);
	}

	float CurrentRotation = GetMesh()->GetRelativeRotation().Euler().Z;
	if (CurrentRotation != TargetRotation) // if the character is not at the target rotation
	{
		float Differance = TargetRotation - CurrentRotation; // differance between where we are and where we need to be
		float Step = (RotationRate * DeltaTime); // the rotation that is performed per frame
		//UE_LOG(LogTemp, Warning, TEXT("CurrentRoll=%f, TargetRotation=%f, Differance=%f"), CurrentRoll, TargetRotation, Differance);

		if (Differance < (Step*1.1) && Differance > -(Step*1.1)) // is the differance smaller than the step I would take?
		{
			// set rotation to target instead of where the step would take us
			GetMesh()->SetRelativeRotation(FRotator::MakeFromEuler(FVector(0, 0, TargetRotation)));
			//UE_LOG(LogTemp, Warning, TEXT("Inside Step=%f"), step);
		}
		else
		{
			float NewRotation;
			if ((Differance < 0 && Differance > -180) || Differance > 180) // do we turn left(counter clockwise) or right(clockwise)
			{
				NewRotation = CurrentRotation - Step; // counter clockwise step
			}
			else
			{
				NewRotation = CurrentRotation + Step; // clockwise step
			}
			GetMesh()->SetRelativeRotation(FRotator::MakeFromEuler(FVector(0, 0, NewRotation)));
			//UE_LOG(LogTemp, Warning, TEXT("NewRoll=%f, Step=%f"), NewRoll, step);
		}
	}
}

// Called to bind functionality to input
void AActivityCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AActivityCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AActivityCharacter::MoveRight);

	PlayerInputComponent->BindAction(TEXT("Scanner"), EInputEvent::IE_Pressed, this, &AActivityCharacter::ScanButtonPress);
}

void AActivityCharacter::MoveForward(float AxisValue)
{
	if (CharactersScanner->ShowingResults || CharactersScanner->ScanInProgress) return;

	AddMovementInput(GetActorForwardVector() * AxisValue);
	Movement.Y = AxisValue;
}

void AActivityCharacter::MoveRight(float AxisValue)
{
	if (CharactersScanner->ShowingResults || CharactersScanner->ScanInProgress) return;

	AddMovementInput(GetActorRightVector() * AxisValue);
	Movement.X = AxisValue;
}

void AActivityCharacter::ScanButtonPress()
{
	if (CharactersScanner->ShowingResults || CharactersScanner->ScanInProgress)
	{
		CharactersScanner->CloseScan();
	}
	else
	{
		CharactersScanner->BeginScan();
	}
}
