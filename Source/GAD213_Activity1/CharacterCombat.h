// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MineralArea.h"
#include "Firearm.h"
#include "CharacterCombat.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAD213_ACTIVITY1_API UCharacterCombat : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterCombat();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void InteractButtonPress();

	UFUNCTION()
	void InteractButtonReleased();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float CombatRange;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float CombatAngle = 90;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool HasWeaponInHand;

	UFUNCTION(BlueprintCallable)
	AWildlife* ClosestWildlife();

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	AFirearm* CurrentWeapon;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<AFirearm> DefaultWeapon;

	UFUNCTION(BlueprintCallable)
	AFirearm* SpawnWeapon();

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	AWildlife* Target;
};
