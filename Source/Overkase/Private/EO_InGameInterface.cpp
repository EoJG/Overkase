// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_InGameInterface.h"
#include <UMG/Public/Components/TextBlock.h>
#include <UMG/Public/Components/ProgressBar.h>
#include <UMG/Public/Components/StackBox.h>


void UEO_InGameInterface::NativeConstruct()
{
	Super::NativeConstruct();
	
	curTime = limitTime;
	text_Score->SetText(FText::AsNumber(score));
}

void UEO_InGameInterface::NativeTick(const FGeometry& Geometry, float DeltaSeconds)
{
	Super::NativeTick(Geometry, DeltaSeconds);

	curTime -= DeltaSeconds;

	SetTimerUI();

	if (menuCount < 5)
	{
		menuCurTime += DeltaSeconds;
		if (menuCurTime >= menuCoolTime)
		{
			SpawnMenu(FMath::RandRange(0, 2));
			menuCurTime = 0;
		}
	}
}

void UEO_InGameInterface::SetTimerUI()
{
	int minute = curTime / 60;
	int second = FMath::Fmod(curTime, 60);

	text_Minute->SetText(FText::FromString(FString::Printf(TEXT("%02d"), minute)));
	text_Second->SetText(FText::FromString(FString::Printf(TEXT("%02d"), second)));

	progress_Timer->SetPercent(curTime / limitTime);
}

void UEO_InGameInterface::SpawnMenu(int randomNum)
{
	switch (randomNum)
	{
	case 0:
		menuSlot = CreateWidget<UEO_Menu>(GetWorld(), cucumberSushiMenu);
		cucumberArr.Add(menuSlot);
		break;
	case 1:
		menuSlot = CreateWidget<UEO_Menu>(GetWorld(), fishSushiMenu);
		fishArr.Add(menuSlot);
		break;
	case 2:
		menuSlot = CreateWidget<UEO_Menu>(GetWorld(), octopusSushiMenu);
		octopusArr.Add(menuSlot);
		break;
	}

	st_MenuList->AddChild(menuSlot);
	menuCount++;
}

void UEO_InGameInterface::SubmitMenu(FName foodTag)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), foodTag);
	if (foodTag == TEXT("CucumberSushi"))
	{
		if (cucumberArr.Num() != 0)
		{
			st_MenuList->RemoveChild(cucumberArr[0]);
			cucumberArr.RemoveAt(0);
			AddScore();
			text_Score->SetText(FText::AsNumber(score));

			menuCount--;
		}
	}
	else if (foodTag == TEXT("FishSushi"))
	{
		if (fishArr.Num() != 0)
		{
			st_MenuList->RemoveChild(fishArr[0]);
			fishArr.RemoveAt(0);
			AddScore();
			text_Score->SetText(FText::AsNumber(score));

			menuCount--;
		}
	}
	else if (foodTag == TEXT("OctopusSushi"))
	{
		if (octopusArr.Num() != 0)
		{
			st_MenuList->RemoveChild(octopusArr[0]);
			octopusArr.RemoveAt(0);
			AddScore();
			text_Score->SetText(FText::AsNumber(score));

			menuCount--;
		}
	}
}

void UEO_InGameInterface::AddScore()
{
	int random = FMath::RandRange(1, 4);
	int plusPoint = 0;

	switch (random)
	{
	case 1:
		plusPoint = 5;
		break;
	case 2:
		plusPoint = 6;
		break;
	case 3:
		plusPoint = 7;
		break;
	case 4:
		plusPoint = 8;
		break;
	}

	score += 60 + plusPoint;
}
