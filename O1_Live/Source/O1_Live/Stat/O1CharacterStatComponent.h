// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Stat/O1CharacterStat.h"
#include "O1CharacterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHpZeroDelegate);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHpChangedDelegate, float /*CurrentHp*/);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStatChangedDelegate, const FO1CharacterStat& /*BaseStat*/, const FO1CharacterStat& /*ModifierStat*/);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class O1_LIVE_API UO1CharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UO1CharacterStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

public:
	void SetupLevel(int32 NewLevel);
	float ApplyDamage(float InDamage);

public:
	FORCEINLINE float GetCurrentLevel() { return CurrentLevel; }
	FORCEINLINE float GetCurrentHp() { return CurrentHp; }
	FORCEINLINE const FO1CharacterStat& GetBaseStat() { return BaseStat; }
	FORCEINLINE const FO1CharacterStat& GetModifierStat() { return ModifierStat; }
	FORCEINLINE FO1CharacterStat GetTotalStat() { return BaseStat + ModifierStat; }

public:
	FORCEINLINE void SetHp(float NewHp)
	{
		CurrentHp = FMath::Clamp<float>(NewHp, 0.0f, GetTotalStat().MaxHp);
		OnHpChanged.Broadcast(CurrentHp);
	}

	FORCEINLINE void AddHp(float InHp)
	{
		CurrentHp = FMath::Clamp<float>(CurrentHp + InHp, 0.0f, GetTotalStat().MaxHp);
		OnHpChanged.Broadcast(CurrentHp);
	}

	FORCEINLINE void SetBaseStat(const FO1CharacterStat& InBaseStat)
	{
		BaseStat = InBaseStat;
		OnStatChanged.Broadcast(GetBaseStat(), GetModifierStat());
	}

	FORCEINLINE void SetModifierStat(const FO1CharacterStat& InModiferStat)
	{
		ModifierStat = InModiferStat;
		OnStatChanged.Broadcast(GetBaseStat(), GetModifierStat());
	}

	FORCEINLINE void AddBaseStat(const FO1CharacterStat& InAddBaseStat)
	{
		BaseStat = BaseStat + InAddBaseStat;
		OnStatChanged.Broadcast(GetBaseStat(), GetModifierStat());
	}

	FORCEINLINE void AddModifierStat(const FO1CharacterStat& InAddModifierStat)
	{
		ModifierStat = ModifierStat + InAddModifierStat;
		OnStatChanged.Broadcast(GetBaseStat(), GetModifierStat());
	}

public:
	FOnHpZeroDelegate OnHpZero;
	FOnHpChangedDelegate OnHpChanged;
	FOnStatChangedDelegate OnStatChanged;

private:
	UPROPERTY(VisibleAnywhere, Category = Stat)
	float CurrentLevel;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	float CurrentHp;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	FO1CharacterStat BaseStat;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	FO1CharacterStat ModifierStat;
		
};
