// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "System/Skill/SkillDataDef.h"
#include "SKillComponent.generated.h"

class ISkillConfirmInterface;
class AMainCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MOUNTAINANDSEA_API USKillComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USKillComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	int32 m_nCurrentSkillId;

	ESkillPhaseEnum m_nSkillPhase;

	TSharedPtr<ISkillConfirmInterface> m_pSkillConfirm;

	AMainCharacter * m_pMainCharacter;

	TSharedPtr<FSkillDataBase> m_pCurrentSkillData;

protected:
	bool m_bIsGroup;

	bool LoadCharOperationType();

	void SaveCharOperationType();

	void ChangeSkillOperationType(bool newType);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OnChangePhase(); 

	void StartSkill(const FSkillDataBase * skillData);

	bool ValidateSkill(const FSkillDataBase * skillData);

protected:
	void _preparePlaySkill();

	void _playingSkill();

	void _endingSkill();
public:
	UFUNCTION(BlueprintCallable)
	void InterruptSkill();

public://Response skill keyboard 
	void ResponseSkillkeyboard(const int8 &key);

	UFUNCTION(BlueprintCallable, Server, Unreliable, WithValidation)
		void RPC_Server_LunchSkill(int32 nSkillID);
	bool RPC_Server_LunchSkill_Validate(int32 nSkillID);
	void RPC_Server_LunchSkill_Implementation(int32 nSkillID);

	void LunchSkill();

	bool GetSkillIsAllowMove() const ;

 	UFUNCTION(BlueprintCallable)
 		void SpawnSkill();
};
