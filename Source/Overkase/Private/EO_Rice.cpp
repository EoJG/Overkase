// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_Rice.h"

AEO_Rice::AEO_Rice()
{
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(TEXT("Rice"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> meshTemp(TEXT("'/Game/Models/Probs/02/m_plated_rice.m_plated_rice'"));
	if (meshTemp.Succeeded())
	{
		meshComp->SetStaticMesh(meshTemp.Object);
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh> changeMeshTemp(TEXT("'/Game/Models/Probs/02/ingredients_rice_boiled.ingredients_rice_boiled'"));
	if (changeMeshTemp.Succeeded())
	{
		changeMeshComp->SetStaticMesh(changeMeshTemp.Object);
	}
}

void AEO_Rice::BeginPlay()
{
	Super::BeginPlay();

	bCanBoil = true;
	coolTime = 3;
}
