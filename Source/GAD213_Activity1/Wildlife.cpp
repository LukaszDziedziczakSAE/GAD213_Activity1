// Fill out your copyright notice in the Description page of Project Settings.


#include "Wildlife.h"

// Sets default values
AWildlife::AWildlife()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	SetRootComponent(CapsuleComponent);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(CapsuleComponent);

	Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
}

// Called when the game starts or when spawned
void AWildlife::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWildlife::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

