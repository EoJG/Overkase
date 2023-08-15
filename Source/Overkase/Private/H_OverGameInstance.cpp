// Fill out your copyright notice in the Description page of Project Settings.


#include "H_OverGameInstance.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"

UH_OverGameInstance::UH_OverGameInstance() {

	overSessionName = TEXT("Overkase");
}

void UH_OverGameInstance::Init()
{
	Super::Init();

	if (IOnlineSubsystem* subsys = IOnlineSubsystem::Get())
	{
		//Online Session Interface API 접근용 인스턴스 가져오기
		sessionInterface = subsys->GetSessionInterface();

		sessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UH_OverGameInstance::OnCreateMySession);

		CreateMySession();

	}
}

void UH_OverGameInstance::CreateMySession()
{
	FOnlineSessionSettings sessionSettings;

	sessionSettings.bIsDedicated = false;
	sessionSettings.bIsLANMatch = true;
	//sessionSettings.bIsLANMatch = IOnlineSubsystem::Get()->GetSubsystemName() == FName("NULL");


	sessionSettings.bShouldAdvertise = true;
	sessionSettings.bUsesPresence = true;
	sessionSettings.bAllowJoinInProgress = true;
	sessionSettings.bAllowJoinViaPresence = true;
	sessionSettings.NumPublicConnections = 4;

	sessionInterface->CreateSession(0, FName("Over Room"), sessionSettings);

}

void UH_OverGameInstance::OnCreateMySession(FName sessionName, bool bWasSuccessful)
{

	if (bWasSuccessful)
	{
		bool result = GetWorld()->ServerTravel("/Game/Maps/SHMap?Listen");
		UE_LOG(LogTemp, Warning, TEXT("Travel Result: %s"), result ? *FString("Success") : *FString("Failed..."));

	}
}
