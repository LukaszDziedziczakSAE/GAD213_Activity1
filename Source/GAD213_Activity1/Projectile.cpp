// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Wildlife.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	SetRootComponent(BoxComp);
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnOverlapStart);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(BoxComp);


}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Position = GetActorLocation();
	Position += GetActorForwardVector() * Speed * DeltaTime;
	SetActorLocation(Position);
}

void AProjectile::OnOverlapStart(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AProjectile* Projectile = Cast<AProjectile>(OtherActor);
	if (Projectile != nullptr) return;

	//UE_LOG(LogTemp, Warning, TEXT("%s Hit %s"), *GetName(), *OtherActor->GetName());

	AWildlife* Wildlife = Cast<AWildlife>(OtherActor);
	if (Wildlife != nullptr)
	{
		Wildlife->Health->CurrentHealth -= Damage;
	}

	Destroy();
}

