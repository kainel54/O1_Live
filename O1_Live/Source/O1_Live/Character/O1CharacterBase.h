// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "O1CharacterBase.generated.h"

struct FO1CharacterStat;

UCLASS()
class O1_LIVE_API AO1CharacterBase : public ACharacter
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

	int32 GetLevel();
	void SetLevel(int32 InNewLevel);

	void ApplyStat(const FO1CharacterStat& BaseStat, const FO1CharacterStat& ModifierStat);

	// Inherited via IB1ItemInterface
	//void TakeItem(UB1ItemData* InItemData) override;
	/*virtual void EquipWeapon(class UB1ItemData* InItemData);
	virtual void DrinkPotion(class UB1ItemData* InItemData);
	virtual void ReadScroll(class UB1ItemData* InItemData);*/

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UO1CharacterStatComponent> StatComponent;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	//TObjectPtr<class UWidgetComponent> HpBarWidgetComponent;

	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USkeletalMeshComponent> WeaponComponent;

	TMap<EItemType, FOnTakeItemDelegate> TakeItemActions;*/
#pragma endregion

#pragma region Attack
public:
//	virtual void ProcessAttack();
//	virtual void ProcessComboAttack();
//
//	virtual void ComboActionBegin();
//	virtual void ComboActionEnd(class UAnimMontage* TargetMontage, bool IsPropertyEnded);
//
//	void SetComboCheckTimer();
//	void ComboCheck();
//
	virtual void SetDead();
	//
	//protected:
	//	UPROPERTY(EditAnywhere)
	//	TObjectPtr<class UAnimMontage> AttackMontage;
	//
	//	UPROPERTY(EditAnywhere)
	//	TObjectPtr<class UAnimMontage> ComboAttackMontage;
	//
	//	UPROPERTY(EditAnywhere)
	//	TObjectPtr<class UAnimMontage> DeadMontage;
	//
	//	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	//	TObjectPtr<class UB1ComboActionData> ComboAttackData;
	//
	//	int32 CurrentCombo = 0;
	//	FTimerHandle ComboTimerHandle;
	//	bool HasNextComboAttack = false;
	//#pragma endregion


	//public:
	//	// Inherited via IB1AttackInterface
	//	virtual void AttackHitCheck() override;


};