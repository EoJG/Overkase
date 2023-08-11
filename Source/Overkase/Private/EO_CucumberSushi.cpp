// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_CucumberSushi.h"

AEO_CucumberSushi::AEO_CucumberSushi()
{
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(TEXT("CucumberSushi"));

	boxComp->SetBoxExtent(FVector(32, 32, 15));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> meshTemp(TEXT("'/Game/Models/Re/Food_/SF_recipe_Cucumber.SF_recipe_Cucumber'"));
	if (meshTemp.Succeeded())
	{
		meshComp->SetStaticMesh(meshTemp.Object);
		meshComp->SetRelativeLocation(FVector(0, 0, -20));
	}
}

void AEO_CucumberSushi::BeginPlay()
{
	Super::BeginPlay();

	bIsComplete = true;
}
