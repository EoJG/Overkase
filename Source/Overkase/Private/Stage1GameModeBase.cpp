// Fill out your copyright notice in the Description page of Project Settings.


#include "Stage1GameModeBase.h"

AStage1GameModeBase::AStage1GameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FClassFinder<AEO_CucumberSushi> cSushiTemp = TEXT("'/Game/Eo/Blueprints/Food/BP_CucumberSushi.BP_CucumberSushi_C'");
	if (cSushiTemp.Succeeded())
	{
		cucumberSushi = cSushiTemp.Class;
	}
	ConstructorHelpers::FClassFinder<AEO_FishSushi> fSushiTemp = TEXT("'/Game/Eo/Blueprints/Food/BP_FishSushi.BP_FishSushi_C'");
	if (fSushiTemp.Succeeded())
	{
		fishSushi = fSushiTemp.Class;
	}
	ConstructorHelpers::FClassFinder<AEO_OctopusSushi> oSushiTemp = TEXT("'/Game/Eo/Blueprints/Food/BP_OctopusSushi.BP_OctopusSushi_C'");
	if (oSushiTemp.Succeeded())
	{
		octopusSushi = oSushiTemp.Class;
	}
}

void AStage1GameModeBase::BeginPlay()
{
	Super::BeginPlay();

}
