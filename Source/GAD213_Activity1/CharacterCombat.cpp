// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterCombat.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "ActivityCharacter.h"
#include "Wildlife.h"

// Sets default values for this component's properties
UCharacterCombat::UCharacterCombat()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCharacterCombat::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCharacterCombat::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	if (CurrentWeapon != nullptr && CurrentWeapon->CanFire() && Target != nullptr)
	{
		CurrentWeapon->Fire(UKismetMathLibrary::FindLookAtRotation(CurrentWeapon->GetMuzzleLocation(), Target->GetActorLocation()));
	}
}

void UCharacterCombat::InteractButtonPress()
{
	UE_LOG(LogTemp, Warning, TEXT("Interact Button Press"));
	//AWildlife* WildLife = ClosestWildlife();
	Target = ClosestWildlife();
	if (Target == nullptr) return;
	SpawnWeapon();
}

void UCharacterCombat::InteractButtonReleased()
{
	if (CurrentWeapon != nullptr)
	{
		CurrentWeapon->Destroy();
		CurrentWeapon = nullptr;
		Target = nullptr;
		HasWeaponInHand = false;
	}
}

AWildlife* UCharacterCombat::ClosestWildlife()
{
	const FVector Start = GetOwner()->GetActorLocation();
	const FVector End = GetOwner()->GetActorLocation();

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetOwner());

	TArray<FHitResult> HitArray;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));

	const bool Hit = UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), Start, End, CombatRange, ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::None, HitArray, true, FLinearColor::Red, FLinearColor::Blue, 20.0f);

	if (Hit)
	{
		TArray<AWildlife*> Wildlifes;
		AActivityCharacter* ActivityCharacter = Cast<AActivityCharacter>(GetOwner());
		float PlayerRotation = ActivityCharacter->GetCurrentMeshRotation();
		float Min = PlayerRotation - (CombatAngle / 2);
		float Max = PlayerRotation + (CombatAngle / 2);
		UE_LOG(LogTemp, Warning, TEXT("Current rotation: %f, Min: %f, Max: %f"), PlayerRotation, Min, Max);

		for (const FHitResult HitResult : HitArray)
		{
			AWildlife* Wildlife = Cast<AWildlife>(HitResult.GetActor());
			if (Wildlife != nullptr)
			{
				FVector Vector = Wildlife->GetActorLocation() - GetOwner()->GetActorLocation();
				float LookAtRotation = (FMath::Atan2(Vector.Y, Vector.X)) * (180 / PI);
				//LookAtRotation -= 180;
				

				if (LookAtRotation >= Min && LookAtRotation <= Max && Wildlife->Health->IsAlive())
				{
					UE_LOG(LogTemp, Warning, TEXT("%s at %f"), *HitResult.GetActor()->GetName(), LookAtRotation);
					Wildlifes.Add(Wildlife);
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("%s at %f"), *HitResult.GetActor()->GetName(), LookAtRotation);
				}
			}
		}
		UE_LOG(LogTemp, Warning, TEXT("Found %i Wildlife, %i HitArray"), Wildlifes.Num(), HitArray.Num());

		AWildlife* ClosestWildlife = nullptr;
		float ClosestDistance = CombatRange * 2;

		for (AWildlife* Wildlife : Wildlifes)
		{
			float Distance = FVector::Distance(Wildlife->GetActorLocation(), GetOwner()->GetActorLocation());
			if (Distance < ClosestDistance)
			{
				ClosestDistance = Distance;
				ClosestWildlife = Wildlife;
			}
		}

		if (ClosestWildlife != nullptr) return ClosestWildlife;
	}

	return nullptr;
}

AFirearm* UCharacterCombat::SpawnWeapon()
{
	HasWeaponInHand = true;
	CurrentWeapon = GetWorld()->SpawnActor<AFirearm>(DefaultWeapon->GetAuthoritativeClass());
	AActivityCharacter* ActivityCharacter = Cast<AActivityCharacter>(GetOwner());
	//UE_LOG(LogTemp, Warning, TEXT("Does socket exist %b"), ActivityCharacter->GetMesh()->DoesSocketExist(TEXT("RightHand")));
	CurrentWeapon->SetOwner(GetOwner());
	CurrentWeapon->AttachToComponent(ActivityCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("RightHand"));
	//CurrentWeapon->SetActorRelativeLocation(FVector::Zero());

	return CurrentWeapon;
}

