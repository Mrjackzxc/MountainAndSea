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

	int32 m_nSkillPhase;

	TSharedPtr<ISkillConfirmInterface> m_pSkillConfirm;

	AMainCharacter * m_pMainCharacter;

protected:
	bool m_bIsGroup;

	bool LoadCharOperationType();

	void SaveCharOperationType();

	void ChangeSkillOperationType(bool newType);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OnChangePhase(const FSkillDataBase * skillData); 

	void StartSkill(const FSkillDataBase * skillData);

protected:
	void _preparePlaySkill(const FSkillDataBase * skillData);

	void _playingSkill(const FSkillDataBase * skillData);

	void _endingSkill(const FSkillDataBase * skillData);

public://Response skill keyboard 
	UFUNCTION(BlueprintCallable)
	void ResponseSkillkeyboard(FString key);

	UFUNCTION(BlueprintCallable)
	void LunchSkill();
};
