// Fill out your copyright notice in the Description page of Project Settings.

#include "CharBaseInfoDef.h"

// Sets default values
ACharBaseInfoDef::ACharBaseInfoDef()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACharBaseInfoDef::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharBaseInfoDef::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

