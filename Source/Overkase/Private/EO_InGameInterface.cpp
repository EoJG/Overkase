// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_InGameInterface.h"
#include <UMG/Public/Components/TextBlock.h>
#include <UMG/Public/Components/ProgressBar.h>
#include <UMG/Public/Components/StackBox.h>
#include "Net/UnrealNetwork.h"
#include "EO_Manager.h"
#include <Kismet/GameplayStatics.h>
#include "Engine/World.h"
#include "TimerManager.h"
#include "H_OverkaseCharacter.h"
#include <UMG/Public/Components/WidgetSwitcher.h>
#include "EO_Menu.h"


void UEO_InGameInterface::NativeConstruct()
{
	Super::NativeConstruct();

	me = Cast<AH_OverkaseCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), AH_OverkaseCharacter::StaticClass()));

	SetTimer(SetTime);
	text_Score->SetText(FText::AsNumber(0));
}

void UEO_InGameInterface::NativeTick(const FGeometry& Geometry, float DeltaSeconds)
{
	Super::NativeTick(Geometry, DeltaSeconds);
	
	if(curTime>0)
	{
		curTime -= DeltaSeconds;
	}
	else
	{
		ws_InGameSwitcher->SetActiveWidgetIndex(1);
	}

	SetTimerUI();
}

void UEO_InGameInterface::SetTimerUI()
{
	int minute = curTime / 60;
	int second = FMath::CeilToInt(FMath::Fmod(curTime, 60));

	text_Minute->SetText(FText::FromString(FString::Printf(TEXT("%02d"), minute)));
	text_Second->SetText(FText::FromString(FString::Printf(TEXT("%02d"), second)));

	progress_Timer->SetPercent(curTime / limitTime);
}

void UEO_InGameInterface::ServerSpawnMenu_Implementation()
{
	//UE_LOG(LogTemp,Warning,TEXT("server"));
	randomNum = FMath::RandRange(0, 2);
	auto pawn = Cast<AH_OverkaseCharacter>(GetOwningPlayer()->GetPawn());

	pawn->SendMulticast(randomNum);
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
	text_Score->SetText(FText::AsNumber(score));

	UE_LOG(LogTemp, Warning, TEXT("%d"), score);
}

void UEO_InGameInterface::SpawnMenu(int random)
{
	if(menuCount<5)
	{
		switch (random)
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
			ServerAddScore();

			menuCount--;
		}
	}
	else if (foodTag == TEXT("FishSushi"))
	{
		if (fishArr.Num() != 0)
		{
			st_MenuList->RemoveChild(fishArr[0]);
			fishArr.RemoveAt(0);
			ServerAddScore();

			menuCount--;
		}
	}
	else if (foodTag == TEXT("OctopusSushi"))
	{
		if (octopusArr.Num() != 0)
		{
			st_MenuList->RemoveChild(octopusArr[0]);
			octopusArr.RemoveAt(0);
			auto pawn = Cast<AH_OverkaseCharacter>(GetOwningPlayer()->GetPawn());
			ServerAddScore();

			menuCount--;
		}
	}
}

void UEO_InGameInterface::ServerAddScore_Implementation()
{
	auto pawn = Cast<AH_OverkaseCharacter>(GetOwningPlayer()->GetPawn());
	if (pawn)
	{
	pawn->MulticastAddScore();
	}
}

void UEO_InGameInterface::SetTimer(float settingTime)
{
	limitTime = settingTime;
	curTime = limitTime;
}

void UEO_InGameInterface::ServerSubmitMenu_Implementation(FName foodTag)
{
	UE_LOG(LogTemp,Warning,TEXT("Server"));
	auto pawn = Cast<AH_OverkaseCharacter>(GetOwningPlayer()->GetPawn());
	pawn->MulticastTestFunc(foodTag);
}

void UEO_InGameInterface::MulticastSubmitMenu_Implementation(FName foodTag)
{
	UE_LOG(LogTemp, Warning, TEXT("Multicast"));
	if (foodTag == TEXT("CucumberSushi"))
	{
		if (cucumberArr.Num() != 0)
		{
			st_MenuList->RemoveChild(cucumberArr[0]);
			cucumberArr.RemoveAt(0);
			ServerAddScore();
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
			ServerAddScore();
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
			ServerAddScore();
			text_Score->SetText(FText::AsNumber(score));

			menuCount--;
		}
	}
	
}


void UEO_InGameInterface::ServerTestFunc_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("ServerCall"));

	MulticastTestFunc();
}

void UEO_InGameInterface::MulticastTestFunc_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("MulticastCall"));
}

void UEO_InGameInterface::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UEO_InGameInterface, curTime);
	DOREPLIFETIME(UEO_InGameInterface, menuCurTime);
	//DOREPLIFETIME(UEO_InGameInterface, score);
	DOREPLIFETIME(UEO_InGameInterface, menuCoolTime);
	DOREPLIFETIME(UEO_InGameInterface, menuCount);
	/*DOREPLIFETIME(UEO_InGameInterface, cucumberArr);
	DOREPLIFETIME(UEO_InGameInterface, fishArr);
	DOREPLIFETIME(UEO_InGameInterface, octopusArr);*/
}
