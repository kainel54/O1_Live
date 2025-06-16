// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/O1CharacterBase.h"
#include "O1Player.generated.h"

struct FInputActionValue;

UENUM(BlueprintType)
enum class ECharacterType : uint8
{
	SwordMan       UMETA(DisplayName = "SwordMan"),
	Guner        UMETA(DisplayName = "Guner"),
	Fighter       UMETA(DisplayName = "Fighter")
};

/**
 *
 */
UCLASS()
class O1_LIVE_API AO1Player : public AO1CharacterBase
{
	GENERATED_BODY()

public:
	AO1Player();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void SetDead() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	//virtual void SetDead() override;
#pragma region InputSystem
private:
	void Input_Attack(const FInputActionValue& InputValue);
	void Input_Move(const FInputActionValue& InputValue);
	void Input_Turn(const FInputActionValue& InputValue);
	void Input_Jump(const FInputActionValue& InputValue);
	void Input_Skill(const FInputActionValue& InputValue);
	void Input_Number(const FInputActionValue& InputValue);

protected:
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<class UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<class UInputAction> AttackAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<class UInputAction> TurnAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<class UInputAction> SkillAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<class UInputAction> NumberAction;

#pragma endregion

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UCameraComponent> Camera;

	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ECharacterType CharacterType;*/
};
