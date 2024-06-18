// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MineralArea.h"
#include "CharactersScanner.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FScannerDelegate);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAD213_ACTIVITY1_API UCharactersScanner : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharactersScanner();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** How long it takes to perform a scan */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float ScanTime;

	/** How big of a radius the scan may reach */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float ScanRange;

	UFUNCTION(BlueprintCallable)
	void BeginScan();

	UFUNCTION(BlueprintCallable)
	void CloseScan();

	UFUNCTION(BlueprintCallable)
	void ShowResults();

	UPROPERTY(BlueprintAssignable)
	FScannerDelegate CharactersScanner_OnScanStart;

	UPROPERTY(BlueprintAssignable)
	FScannerDelegate CharactersScanner_OnScanComplete;

	UPROPERTY(BlueprintAssignable)
	FScannerDelegate CharactersScanner_OnScanClose;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	bool ScanInProgress;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	bool ShowingResults;

	UPROPERTY(VisibleAnywhere)
	float StartTime;

	UFUNCTION(BlueprintCallable)
	float GetElapsedTime();

	UFUNCTION(BlueprintCallable)
	float GetScanProgress();

	UPROPERTY(VisibleAnywhere)
	AMineralArea* MineralArea;

	UFUNCTION(BlueprintCallable)
	AMineralArea* ClosestMineralArea();

	UFUNCTION(BlueprintCallable)
	float GetResultDirection();

	UFUNCTION(BlueprintCallable)
	int GetResultsGrade();

	UPROPERTY(EditDefaultsOnly)
	float Grade1;

	UPROPERTY(EditDefaultsOnly)
	float Grade2;

	UPROPERTY(EditDefaultsOnly)
	float Grade3;

	UPROPERTY(EditDefaultsOnly)
	float Grade4;
};
