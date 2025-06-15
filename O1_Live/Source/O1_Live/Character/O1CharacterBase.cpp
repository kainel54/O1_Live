// Fill out your copyright notice in the Description page of Project Settings.


#include "O1CharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

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
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceRef(TEXT("/Script/Engine.AnimBlueprint'/Game/ParagonAurora/Characters/Heroes/Aurora/Aurora_AnimBlueprint.Aurora_AnimBlueprint'"));
	if (AnimInstanceRef.Succeeded())
	{
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		GetMesh()->SetAnimInstanceClass(AnimInstanceRef.Class);
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
    return 0.0f;
}

int32 AO1CharacterBase::GetLevel()
{
    return int32();
}

void AO1CharacterBase::ApplyStat(const FO1CharacterStat& BaseStat, const FO1CharacterStat& ModifierStat)
{

}

void AO1CharacterBase::SetDead()
{
}
