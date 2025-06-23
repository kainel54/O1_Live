// Fill out your copyright notice in the Description page of Project Settings.


#include "O1CharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Stat/O1CharacterStatComponent.h"
#include "Kismet/GameplayStatics.h"
#include "O1ComboAttackData.h"
#include "Engine/DamageEvents.h"

// Fill out your copyright notice in the Description page of Project Settings.


// Sets default values
AO1CharacterBase::AO1CharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Pawn
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Capsule
	GetCapsuleComponent()->InitCapsuleSize(34.0f, 88.0f);

	// Movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);

	// Mesh
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> FindMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonAurora/Characters/Heroes/Aurora/Meshes/Aurora.Aurora'"));

	if (FindMeshRef.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(FindMeshRef.Object);
	}

	// Animation
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceRef(TEXT("/Script/Engine.AnimBlueprint'/Game/Animation/ABP_Aurora.ABP_Aurora'"));
	if (AnimInstanceRef.Succeeded())
	{
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		GetMesh()->SetAnimInstanceClass(AnimInstanceRef.Class);
	}

	StatComponent = CreateDefaultSubobject<UO1CharacterStatComponent>(TEXT("Stat"));


	static ConstructorHelpers::FObjectFinder<UO1ComboAttackData> ComboActionDataRef(TEXT("/Script/O1_Live.O1ComboAttackData'/Game/AssetData/DA_AuroraComboAttackData.DA_AuroraComboAttackData'"));
	if (ComboActionDataRef.Succeeded())
	{
		ComboAttackData = ComboActionDataRef.Object;
	}
}

// Called when the game starts or when spawned
void AO1CharacterBase::BeginPlay()
{
    Super::BeginPlay();

}

void AO1CharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	StatComponent->OnHpZero.AddUObject(this, &AO1CharacterBase::SetDead);
	StatComponent->OnStatChanged.AddUObject(this, &AO1CharacterBase::ApplyStat);
}

// Called every frame
void AO1CharacterBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AO1CharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AO1CharacterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	StatComponent->ApplyDamage(DamageAmount);

	return DamageAmount;
}

void AO1CharacterBase::ApplyStat(const FO1CharacterStat& BaseStat, const FO1CharacterStat& ModifierStat)
{
	float MovementSpeed = (BaseStat + ModifierStat).MovementSpeed;
	GetCharacterMovement()->MaxWalkSpeed = MovementSpeed;
}
void AO1CharacterBase::ProcessComboAttack()
{
	if (CurrentCombo == 0)
	{
		ComboActionBegin();
		return;
	}

	if (ComboTimerHandle.IsValid())
	{
		HasNextComboAttack = true;
	}
	else
	{
		HasNextComboAttack = false;
	}
}

void AO1CharacterBase::ComboActionBegin()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

	// Animation Setting
	CurrentCombo = 1;
	const float AttackSpeedRate = StatComponent->GetTotalStat().AttackSpeed;
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance == nullptr)
		return;

	// Montage Play -> ComboAttack1
	AnimInstance->Montage_Play(ComboAttackMontage, AttackSpeedRate);

	// Montage End Delegate
	FOnMontageEnded EndDelegete;
	EndDelegete.BindUObject(this, &AO1CharacterBase::ComboActionEnd);
	AnimInstance->Montage_SetEndDelegate(EndDelegete, ComboAttackMontage);

	ComboTimerHandle.Invalidate();
	SetComboCheckTimer();
}

void AO1CharacterBase::ComboActionEnd(UAnimMontage* TargetMontage, bool IsPropertyEnded)
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	CurrentCombo = 0;
}

void AO1CharacterBase::SetComboCheckTimer()
{
	int32 ComboIndex = CurrentCombo - 1;
	ensure(ComboAttackData->EffectiveFrameCount.IsValidIndex(ComboIndex));

	const float AttackSpeedRate = StatComponent->GetTotalStat().AttackSpeed;
	float ComboEffectiveTime = (ComboAttackData->EffectiveFrameCount[ComboIndex] / ComboAttackData->FrameRate) / AttackSpeedRate;

	if (ComboEffectiveTime > 0.0f)
	{
		GetWorld()->GetTimerManager().SetTimer(ComboTimerHandle, this, &AO1CharacterBase::ComboCheck, ComboEffectiveTime, false);
	}
}

void AO1CharacterBase::ComboCheck()
{
	ComboTimerHandle.Invalidate();

	if (HasNextComboAttack)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance == nullptr)
			return;

		CurrentCombo = FMath::Clamp(CurrentCombo + 1, 1, ComboAttackData->MaxComboCount);

		FName NextSection = *FString::Printf(TEXT("%s%d"), *ComboAttackData->MontageSectionNamePrefix, CurrentCombo);
		AnimInstance->Montage_JumpToSection(NextSection, ComboAttackMontage);

		SetComboCheckTimer();
		HasNextComboAttack = false;
	}
}

void AO1CharacterBase::SetDead()
{
}

void AO1CharacterBase::AttackHitCheck()
{
	const float AttackRange = StatComponent->GetTotalStat().AttackRange;
	const float AttackRadius = StatComponent->GetTotalStat().AttackRadius;
	const float AttackDamage = StatComponent->GetTotalStat().Attack;

	FHitResult OutHitResult;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack), false, this);

	const FVector Start = GetActorLocation() + GetActorForwardVector() * GetCapsuleComponent()->GetScaledCapsuleRadius();
	const FVector End = Start + GetActorForwardVector() * AttackRange;

	bool HitDetected = GetWorld()->SweepSingleByChannel(OutHitResult, Start, End, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(AttackRadius), Params);

	if (HitDetected)
	{
		FDamageEvent DamageEvent;
		OutHitResult.GetActor()->TakeDamage(AttackDamage, DamageEvent, GetController(), this);

		UGameplayStatics::ApplyDamage(OutHitResult.GetActor(), AttackDamage, GetController(), this, nullptr);
	}

#if ENABLE_DRAW_DEBUG
	FVector CapsuleOrigin = Start + (End - Start) * 0.5f;
	float CapsuleHalfHeight = AttackRange * 0.5f;
	FColor DrawColor = HitDetected ? FColor::Green : FColor::Red;

	DrawDebugCapsule(GetWorld(), CapsuleOrigin, CapsuleHalfHeight, AttackRadius, FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(), DrawColor, false, 5.0f);
#endif
}
