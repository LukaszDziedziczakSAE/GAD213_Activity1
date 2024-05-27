// Fill out your copyright notice in the Description page of Project Settings.


#include "ActivityCharacter.h"

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

}

// Called to bind functionality to input
void AActivityCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

