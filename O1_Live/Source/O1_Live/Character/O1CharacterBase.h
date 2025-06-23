// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/O1AttackInterface.h"
#include "O1CharacterBase.generated.h"

struct FO1CharacterStat;

UCLASS()
class O1_LIVE_API AO1CharacterBase : public ACharacter, public IO1AttackInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AO1CharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

#pragma region CharacterStat
public:

	void ApplyStat(const FO1CharacterStat& BaseStat, const FO1CharacterStat& ModifierStat);
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UO1CharacterStatComponent> StatComponent;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	//TObjectPtr<class UWidgetComponent> HpBarWidgetComponent;

#pragma endregion

#pragma region Attack
public:
	virtual void ProcessComboAttack();

	virtual void ComboActionBegin();
	virtual void ComboActionEnd(class UAnimMontage* TargetMontage, bool IsPropertyEnded);

	void SetComboCheckTimer();
	void ComboCheck();

	virtual void SetDead();
	
	protected:
		UPROPERTY(EditAnywhere)
		TObjectPtr<class UAnimMontage> AttackMontage;
	
		UPROPERTY(EditAnywhere)
		TObjectPtr<class UAnimMontage> ComboAttackMontage;
	
		UPROPERTY(EditAnywhere)
		TObjectPtr<class UAnimMontage> DeadMontage;
	
		UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TObjectPtr<class UO1ComboAttackData> ComboAttackData;
	
		int32 CurrentCombo = 0;
		FTimerHandle ComboTimerHandle;
		bool HasNextComboAttack = false;
	#pragma endregion





		// IO1AttackInterface을(를) 통해 상속됨
		void AttackHitCheck() override;

};