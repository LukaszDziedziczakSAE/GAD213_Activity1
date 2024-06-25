// Fill out your copyright notice in the Description page of Project Settings.


#include "Firearm.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFirearm::AFirearm()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(RootComp);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComp);

	Muzzle = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
	Muzzle->SetupAttachment(Mesh);
}

// Called when the game starts or when spawned
void AFirearm::BeginPlay()
{
	Super::BeginPlay();
	
	LastFireTime = UGameplayStatics::GetRealTimeSeconds(GetWorld()) + (FireRate * 2);
}

// Called every frame
void AFirearm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AFirearm::CanFire()
{
	return UGameplayStatics::GetRealTimeSeconds(GetWorld()) - LastFireTime >= FireRate;
}

void AFirearm::Fire(FRotator MuzzleRotation)
{
	LastFireTime = UGameplayStatics::GetRealTimeSeconds(GetWorld());
	UE_LOG(LogTemp, Warning, TEXT("Weapon Fired"));


	if (ProjectilePrefab == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ProjectilePrefab is null"));
		return;
	}
	
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectilePrefab->GetAuthoritativeClass());

	if (Projectile == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Projectile error"));
		return;
	}

	Projectile->SetActorLocationAndRotation(Muzzle->GetComponentLocation(), MuzzleRotation);
		
}

FVector AFirearm::GetMuzzleLocation()
{
	return Muzzle->GetComponentLocation();
}

