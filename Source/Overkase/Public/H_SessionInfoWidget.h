// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "H_SessionInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class OVERKASE_API UH_SessionInfoWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;

	public:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UTextBlock* text_RoomName;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UTextBlock* text_HostName;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UTextBlock* text_PingSpeed;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UButton* btn_Join;

	int32 sessionIndex = 0;

	UPROPERTY()
	class UH_OverGameInstance* ogi;

	UFUNCTION()
	void OnClickedJoinButton();
};
