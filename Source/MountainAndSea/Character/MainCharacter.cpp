// Fill out your copyright notice in the Description page of Project Settings.

#include "MainCharacter.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "ManRole/MainRoleAnimInstance.h"
#include "Components/InputComponent.h"
#include "Engine/Engine.h"

// Sets default values
AMainCharacter::AMainCharacter():m_fPitchHightLimit(89),m_fPitchLowLimit(-60), BaseTurnRate(1),BaseLookUpRate(1), m_fStatMachine(this)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or w hen spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	m_fRoleRotator = GetActorRotation();
	m_fControllerRotator = GetControlRotation();
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	m_fControllerRotator = GetControlRotation();
	m_fRoleRotator= RootComponent->GetComponentRotation();
}

void AMainCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMainCharacter::DoJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);

// 	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
// 	// "turn" handles devices that provide an absolute delta, such as a mouse.
// 	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
 	PlayerInputComponent->BindAxis("Turn", this, &AMainCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AMainCharacter::AddControllerPitchInput);
//	PlayerInputComponent->BindAxis("TurnRate", this, &AMainCharacter::TurnAtRate);
 //	PlayerInputComponent->BindAxis("LookUpRate", this, &AMountainAndSeaCharacter::LookUpAtRate);

}


void AMainCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator YawRotation(0, m_fControllerRotator.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AMainCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator YawRotation(0, m_fControllerRotator.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AMainCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMainCharacter::LookUpAtRate(float Rate)
{
	if (GetControlRotation().Pitch+(Rate*BaseLookUpRate*GetWorld()->GetDeltaSeconds())>m_fPitchHightLimit||
		GetControlRotation().Pitch + (Rate*BaseLookUpRate*GetWorld()->GetDeltaSeconds())<m_fPitchLowLimit)
	{
		return;
	}
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}



void AMainCharacter::DoJump()
{
	m_fStatMachine.ChangeStat(JumpStat);
}

void AMainCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	m_fStatMachine.ChangeStat(IdleStat);
}

void AMainCharacter::ConsumeHp(int32 value)
{
	m_fHeroBaseInfo.m_nHeroHP = FMath::Clamp(m_fHeroBaseInfo.m_nHeroHP-value,0, m_fHeroBaseInfo.m_nHeroHP);
}

void AMainCharacter::ConsumeMp(int32 value)
{
	m_fHeroBaseInfo.m_nHeroMP = FMath::Clamp(m_fHeroBaseInfo.m_nHeroMP - value, 0, m_fHeroBaseInfo.m_nHeroMP);
}

ECharBaseStat AMainCharacter::GetRoleStat() const
{
	return m_fStatMachine.GetStat();
}

void AMainCharacter::OnRoleStatChange(ECharBaseStat eStat)
{
	UMainRoleAnimInstance * _RoleAnimIns= Cast<UMainRoleAnimInstance>(GetMesh()->GetAnimInstance());
	if (_RoleAnimIns!=nullptr)
	{
		_RoleAnimIns->SetRoleStats(eStat);
	}
}

bool AMainCharacter::ChangeRoleStat(ECharBaseStat eStat)
{
	return m_fStatMachine.ChangeStat(eStat);
}

