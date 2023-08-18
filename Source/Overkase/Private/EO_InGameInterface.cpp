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


void UEO_InGameInterface::NativeConstruct()
{
	Super::NativeConstruct();
	me = Cast<AH_OverkaseCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), AH_OverkaseCharacter::StaticClass()));

	SetTimer(180);
	//ServerSpawnMenu();
	
	//ServerSpawnMenu();

}

void UEO_InGameInterface::NativeTick(const FGeometry& Geometry, float DeltaSeconds)
{
	Super::NativeTick(Geometry, DeltaSeconds);
	
	curTime -= DeltaSeconds;
	SetTimerUI();

	

	//if (menuCount < 5)
	//{
	//	menuCurTime += DeltaSeconds;
	//	if (menuCurTime >= menuCoolTime)
	//	{
	//		me->ServerOnScreenMenu();
	//		//ServerSpawnMenu();
	//		menuCurTime = 0;
	//	}
	//}
}

void UEO_InGameInterface::SetTimerUI()
{
	int minute = curTime / 60;
	int second = FMath::Fmod(curTime, 60);

	text_Minute->SetText(FText::FromString(FString::Printf(TEXT("%02d"), minute)));
	text_Second->SetText(FText::FromString(FString::Printf(TEXT("%02d"), second)));

	progress_Timer->SetPercent(curTime / limitTime);
}


void UEO_InGameInterface::ServerCase0_Implementation()
{
	MulticastCase0();
}

void UEO_InGameInterface::ServerCase1_Implementation()
{
	MulticastCase1();
}

void UEO_InGameInterface::ServerCase2_Implementation()
{
	MulticastCase2();
}

void UEO_InGameInterface::MulticastCase0_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("%MulticastCase0_Implementation"));
	menuSlot = CreateWidget<UEO_Menu>(GetWorld(), cucumberSushiMenu);
	cucumberArr.Add(menuSlot);
}

void UEO_InGameInterface::MulticastCase1_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("%MulticastCase1_Implementation"));

	menuSlot = CreateWidget<UEO_Menu>(GetWorld(), fishSushiMenu);
	fishArr.Add(menuSlot);
}

void UEO_InGameInterface::MulticastCase2_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("%MulticastCase2_Implementation"));

	menuSlot = CreateWidget<UEO_Menu>(GetWorld(), octopusSushiMenu);
	octopusArr.Add(menuSlot);
}


void UEO_InGameInterface::ServerSpawnMenu_Implementation()
{
	UE_LOG(LogTemp,Warning,TEXT("Server"));
	randomNum = FMath::RandRange(0, 2);
	auto pawn = Cast<AH_OverkaseCharacter>(GetOwningPlayer()->GetPawn());
	pawn->SendMulticast(randomNum);

	// 서버는 모든  PC 갖고 있다.
	//TArray<AActor*> pcs;
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerController::StaticClass(), pcs);
	//for (auto playercontroller : pcs)
	//{
	//	auto pc = Cast<APlayerController>(playercontroller);
	//	auto pawn = Cast<AH_OverkaseCharacter>(pc->GetPawn());
	//	//pawn->inGameUI->MulticastSpawnMenu(randomNum);
	//}
	//MulticastSpawnMenu(randomNum);
}

void UEO_InGameInterface::SpawnMenu(int random)
{
	switch (randomNum)
	{
	case 0:
		menuSlot = CreateWidget<UEO_Menu>(GetWorld(), cucumberSushiMenu);
		cucumberArr.Add(menuSlot);
		//ServerCase0();
		break;
	case 1:
		menuSlot = CreateWidget<UEO_Menu>(GetWorld(), fishSushiMenu);
		fishArr.Add(menuSlot);
		//ServerCase1();
		break;
	case 2:
		menuSlot = CreateWidget<UEO_Menu>(GetWorld(), octopusSushiMenu);
		octopusArr.Add(menuSlot);
		//ServerCase2();
		break;
	}
	//UE_LOG(LogTemp, Warning, TEXT("%d"), randomNum);
	st_MenuList->AddChild(menuSlot);
	menuCount++;
}

//void UEO_InGameInterface::SpawnMenu()
//{
//	randomNum = FMath::RandRange(0, 2);
//
//	switch (randomNum)
//	{
//	case 0:
//		menuSlot = CreateWidget<UEO_Menu>(GetWorld(), cucumberSushiMenu);
//		cucumberArr.Add(menuSlot);
//		//MulticastCase0();
//		break;
//	case 1:
//		menuSlot = CreateWidget<UEO_Menu>(GetWorld(), fishSushiMenu);
//		fishArr.Add(menuSlot);
//		//MulticastCase1();
//		break;
//	case 2:
//		menuSlot = CreateWidget<UEO_Menu>(GetWorld(), octopusSushiMenu);
//		octopusArr.Add(menuSlot);
//		//MulticastCase2();
//		break;
//	}
//	//UE_LOG(LogTemp, Warning, TEXT("%d"), randomNum);
//	st_MenuList->AddChild(menuSlot);
//	menuCount++;
//}


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

void UEO_InGameInterface::SetTimer(float settingTime)
{
	limitTime = settingTime;
	curTime = limitTime;
}

void UEO_InGameInterface::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UEO_InGameInterface, curTime);
	DOREPLIFETIME(UEO_InGameInterface, menuCurTime);
	DOREPLIFETIME(UEO_InGameInterface, score);
	DOREPLIFETIME(UEO_InGameInterface, menuCoolTime);
	/*DOREPLIFETIME(UEO_InGameInterface, cucumberArr);
	DOREPLIFETIME(UEO_InGameInterface, fishArr);
	DOREPLIFETIME(UEO_InGameInterface, octopusArr);
	DOREPLIFETIME(UEO_InGameInterface, cucumberSushiMenu);
	DOREPLIFETIME(UEO_InGameInterface, fishSushiMenu);
	DOREPLIFETIME(UEO_InGameInterface, octopusSushiMenu);*/
}
