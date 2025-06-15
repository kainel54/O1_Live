// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "O1CharacterStat.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FO1CharacterStat : public FTableRowBase
{
	GENERATED_BODY()

public:
	FO1CharacterStat() : MaxHp(0.f), Attack(0.f), AttackRange(0.f), AttackRadius(0.f), AttackSpeed(0.f), MovementSpeed(0.f) {}

public:
	FO1CharacterStat operator+(const FO1CharacterStat& Other) const
	{
		const float* const ThisPtr = reinterpret_cast<const float* const>(this);
		const float* const OtherPtr = reinterpret_cast<const float* const>(&Other);

		FO1CharacterStat Result;
		float* ResultPtr = reinterpret_cast<float*>(&Result);

		int32 StatNum = sizeof(FO1CharacterStat) / sizeof(float);
		for (int32 i = 0; i < StatNum; ++i)
		{
			ResultPtr[i] = ThisPtr[i] + OtherPtr[i];
		}

		return Result;
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MovementSpeed;
};
