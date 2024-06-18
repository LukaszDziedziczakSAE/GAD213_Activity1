// Fill out your copyright notice in the Description page of Project Settings.


#include "MineralArea.h"

// Sets default values
AMineralArea::AMineralArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SetRootComponent(Sphere);
}

// Called when the game starts or when spawned
void AMineralArea::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMineralArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

