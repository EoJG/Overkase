// Fill out your copyright notice in the Description page of Project Settings.


#include "Stage1GameModeBase.h"
#include <Kismet/GameplayStatics.h>
#include <UMG/Public/Blueprint/UserWidget.h>
#include "EO_InGameInterface.h"

AStage1GameModeBase::AStage1GameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;

	
}

void AStage1GameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	
}



//void AStage1GameModeBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
//{
//	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//
//	DOREPLIFETIME(AStage1GameModeBase, inGameUIClass);
//	DOREPLIFETIME(AStage1GameModeBase, inGameUI);
//}
