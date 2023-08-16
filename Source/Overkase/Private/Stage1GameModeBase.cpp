// Fill out your copyright notice in the Description page of Project Settings.


#include "Stage1GameModeBase.h"
#include <Kismet/GameplayStatics.h>

AStage1GameModeBase::AStage1GameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<UEO_InGameInterface> menuTemp(TEXT("'/Game/Eo/Blueprints/UI/BP_UI_InGameInterface.BP_UI_InGameInterface_C'"));
	if (menuTemp.Succeeded())
	{
		menuInterface = menuTemp.Class;
	}

	static ConstructorHelpers::FClassFinder<AEO_OrderTable> orderTemp(TEXT("'/Game/Eo/Blueprints/Object/BP_OrderTable.BP_OrderTable_C'"));
	if (orderTemp.Succeeded())
	{
		orderTable = orderTemp.Class;
	}
}

void AStage1GameModeBase::BeginPlay()
{
	Super::BeginPlay();

	/*UUserWidget* menu;
	menu = CreateWidget(GetWorld(), menuInterface);
	menu->AddToViewport();
	Cast<AEO_OrderTable>(UGameplayStatics::GetActorOfClass(GetWorld(), orderTable))->menuInter = Cast<UEO_InGameInterface>(menu);*/
}
