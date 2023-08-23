// Fill out your copyright notice in the Description page of Project Settings.


#include "Stage1GameModeBase.h"
#include <Kismet/GameplayStatics.h>
#include <UMG/Public/Blueprint/UserWidget.h>
#include "EO_InGameInterface.h"

AStage1GameModeBase::AStage1GameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;

	/*ConstructorHelpers::FObjectFinder<USoundBase> TempBGM(TEXT("/Script/Engine.SoundWave'/Game/HanSeunghui/Sound/y2mate_com-Overcooked-2-Soundtrack-Sushi-City.y2mate_com-Overcooked-2-Soundtrack-Sushi-City'"));
	if (TempBGM.Succeeded())
	{
		BGMSound = TempBGM.Object;
	}*/
}

void AStage1GameModeBase::BeginPlay()
{
	Super::BeginPlay();
	//UGameplayStatics::PlaySound2D(this, BGMSound);
	
}



//void AStage1GameModeBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
//{
//	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//
//	DOREPLIFETIME(AStage1GameModeBase, inGameUIClass);
//	DOREPLIFETIME(AStage1GameModeBase, inGameUI);
//}
