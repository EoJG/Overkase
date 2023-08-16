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
		sessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UH_OverGameInstance::OnFindOtherSessions);
		sessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UH_OverGameInstance::OnJoinSelectedSession);
	}
}

void UH_OverGameInstance::CreateMySession(FText roomName)
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

	sessionSettings.Set(FName("ROOM_NAME"), roomName.ToString(), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	sessionSettings.Set(FName("HOST_NAME"), overSessionName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
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

void UH_OverGameInstance::FindOtherSession()
{
	sessionSearch = MakeShareable(new FOnlineSessionSearch());
	// 1. 세션 검색을 LAN으로 할 것인지 여부를 설정한다.
	sessionSearch->bIsLanQuery = IOnlineSubsystem::Get()->GetSubsystemName() == FName("NULL");

	// 2. 세션 쿼리(query) 설정한다.
	sessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);

	// 3. 세션의 검색량을 설정한다.
	sessionSearch->MaxSearchResults = 50;

	sessionInterface->FindSessions(0, sessionSearch.ToSharedRef());
	onFindButtonActivation.Broadcast(false);
}

void UH_OverGameInstance::OnFindOtherSessions(bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		// 검색된 세션 목록을 가져온다.
		TArray<FOnlineSessionSearchResult> searchResults = sessionSearch->SearchResults;

		UE_LOG(LogTemp, Warning, TEXT("Find Sessions: %d"), searchResults.Num());

		for (int32 i = 0; i < searchResults.Num(); i++)
		{
			FString roomName;
			searchResults[i].Session.SessionSettings.Get(FName("ROOM_NAME"), roomName);
			FString hostName;
			searchResults[i].Session.SessionSettings.Get(FName("HOST_NAME"), hostName);
			int32 openNumber = searchResults[i].Session.NumOpenPublicConnections;
			int32 maxNumber = searchResults[i].Session.SessionSettings.NumPublicConnections;
			int32 pingSpeed = searchResults[i].PingInMs;

			UE_LOG(LogTemp, Warning, TEXT("Room Name: %s, HostName: %s, OpenNumber: %d, MaxNumber: %d, Ping Speed: %d"), *roomName, *hostName, openNumber, maxNumber, pingSpeed);

			// 구조체 변수에 찾은 세션 정보를 입력한다.
			FSessionSlotInfo slotInfo;
			slotInfo.Set(roomName, hostName, FString::Printf(TEXT("(%d/%d)"), maxNumber - openNumber, maxNumber), pingSpeed, i);

			// 세션 정보를 델리게이트로 전파한다.
			onSearchCompleted.Broadcast(slotInfo);
		}

		onFindButtonActivation.Broadcast(true);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Session search failed..."));
	}
}

void UH_OverGameInstance::JoinSelectedSession(int32 index)
{
	sessionInterface->JoinSession(0, FName(overSessionName), sessionSearch->SearchResults[index]);
}

void UH_OverGameInstance::OnJoinSelectedSession(FName sessionName, EOnJoinSessionCompleteResult::Type result)
{
	switch (result)
	{
	case EOnJoinSessionCompleteResult::Success:
	{
		UE_LOG(LogTemp, Warning, TEXT("Success: %s"), *sessionName.ToString());

		APlayerController* playerCon = GetWorld()->GetFirstPlayerController();

		if (playerCon != nullptr)
		{
			// join된 세션 호스트의 ServerTravel 된 맵 주소를 받아온다.
			FString url;
			sessionInterface->GetResolvedConnectString(sessionName, url);
			UE_LOG(LogTemp, Warning, TEXT("Connection URL: %s"), *url);

			// 주소를 받았다면, 그 주소에 따라서 맵 이동한다.
			if (!url.IsEmpty())
			{
				playerCon->ClientTravel(url, ETravelType::TRAVEL_Absolute);
			}
		}

	}
	break;
	case EOnJoinSessionCompleteResult::SessionIsFull:
		UE_LOG(LogTemp, Warning, TEXT("SessionIsFull"));
		break;
	case EOnJoinSessionCompleteResult::SessionDoesNotExist:
		UE_LOG(LogTemp, Warning, TEXT("SessionDoesNotExist"));
		break;
	case EOnJoinSessionCompleteResult::CouldNotRetrieveAddress:
		UE_LOG(LogTemp, Warning, TEXT("CouldNotRetrieveAddress"));
		break;
	case EOnJoinSessionCompleteResult::AlreadyInSession:
		UE_LOG(LogTemp, Warning, TEXT("AlreadyInSession"));
		break;
	case EOnJoinSessionCompleteResult::UnknownError:
		UE_LOG(LogTemp, Warning, TEXT("UnknownError"));
		break;
	default:
		break;
	}
}
