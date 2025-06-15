// Fill out your copyright notice in the Description page of Project Settings.


#include "Stat/O1CharacterStatComponent.h"

// Sets default values for this component's properties
UO1CharacterStatComponent::UO1CharacterStatComponent()
{
	bWantsInitializeComponent = true;
	CurrentLevel = 1.0f;

}

void UO1CharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UO1CharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	SetupLevel(CurrentLevel);
	SetHp(BaseStat.MaxHp);
}

void UO1CharacterStatComponent::SetupLevel(int32 NewLevel)
{
	//CurrentLevel = FMath::Clamp(NewLevel, 1, UB1GameSingleton::Get().GetCharacterMaxLevel());
	//SetBaseStat(UB1GameSingleton::Get().GetCharacterStat(CurrentLevel));
}

float UO1CharacterStatComponent::ApplyDamage(float InDamage)
{
	const float PreHp = CurrentHp;
	const float ActualDamage = FMath::Clamp<float>(InDamage, 0.0f, InDamage);

	SetHp(PreHp - ActualDamage);
	if (CurrentHp <= KINDA_SMALL_NUMBER)
	{
		OnHpZero.Broadcast();
	}
	return ActualDamage;
}
