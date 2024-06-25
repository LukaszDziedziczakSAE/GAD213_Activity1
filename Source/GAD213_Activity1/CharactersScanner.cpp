// Fill out your copyright notice in the Description page of Project Settings.


#include "CharactersScanner.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UCharactersScanner::UCharactersScanner()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCharactersScanner::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCharactersScanner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ScanInProgress && GetElapsedTime() > ScanTime)
	{
		ShowResults();
	}
}

void UCharactersScanner::BeginScan()
{
	UE_LOG(LogTemp, Warning, TEXT("Begining scan"));
	ScanInProgress = true;
	StartTime = UGameplayStatics::GetRealTimeSeconds(GetWorld());

	CharactersScanner_OnScanStart.Broadcast();
}

void UCharactersScanner::CloseScan()
{
	ScanInProgress = false;
	ShowingResults = false;
	CharactersScanner_OnScanClose.Broadcast();
}

void UCharactersScanner::ShowResults()
{
	MineralArea = ClosestMineralArea();
	ScanInProgress = false;
	ShowingResults = MineralArea != nullptr;

	if (ShowingResults) CharactersScanner_OnScanComplete.Broadcast();
	else CharactersScanner_OnScanClose.Broadcast();
}

float UCharactersScanner::GetElapsedTime()
{
	return UGameplayStatics::GetRealTimeSeconds(GetWorld()) - StartTime;
}

float UCharactersScanner::GetScanProgress()
{
	if (!ScanInProgress) return 0.0f;

	float progress = GetElapsedTime() / ScanTime;

	if (progress > 1) progress = 1;

	return progress;
}

AMineralArea* UCharactersScanner::ClosestMineralArea()
{
	const FVector Start = GetOwner()->GetActorLocation();
	const FVector End = GetOwner()->GetActorLocation();

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetOwner());

	TArray<FHitResult> HitArray;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));

	const bool Hit = UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), Start, End, ScanRange, ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::None, HitArray, true, FLinearColor::Red, FLinearColor::Blue, 20.0f);

	if (Hit)
	{
		TArray<AMineralArea*> MineralAreas;

		for (const FHitResult HitResult : HitArray)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Hit %s"), *HitResult.GetActor()->GetName());

			AMineralArea* Area = Cast<AMineralArea>(HitResult.GetActor());
			if (Area != nullptr)
			{
				MineralAreas.Add(Area);
			}
		}
		//UE_LOG(LogTemp, Warning, TEXT("Found %i"), MineralAreas.Num());

		AMineralArea* ClosestArea = nullptr;
		float ClosestDistance = ScanRange * 2;

		for (AMineralArea* Area : MineralAreas)
		{
			float Distance = FVector::Distance(Area->GetActorLocation(), GetOwner()->GetActorLocation());
			if (Distance < ClosestDistance)
			{
				ClosestDistance = Distance;
				ClosestArea = Area;
			}
		}

		if (ClosestArea != nullptr) return ClosestArea;
	}

	return nullptr;
}

float UCharactersScanner::GetResultDirection()
{
	//return FMath::Acos(FVector::DotProduct(GetOwner()->GetActorLocation(), MineralArea->GetActorLocation())) * (180 / PI);
	
	FVector Vector = GetOwner()->GetActorLocation() - MineralArea->GetActorLocation();
	float Direction = (FMath::Atan2(Vector.Y, Vector.X)) * (180 / PI);
	return Direction + 180;
}

int UCharactersScanner::GetResultsGrade()
{
	float Distance = FVector::Distance(MineralArea->GetActorLocation(), GetOwner()->GetActorLocation());

	if (Distance <= Grade4) return 4;
	else if (Distance <= Grade3) return 3;
	else if (Distance <= Grade2) return 2;
	else if (Distance <= Grade1) return 1;
	return 0;
}

