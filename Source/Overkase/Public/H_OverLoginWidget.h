// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "H_OverLoginWidget.generated.h"

/**
 * 
 */
UCLASS()
class OVERKASE_API UH_OverLoginWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UEditableText* edit_roomName;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UButton* btn_CreateSession;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UWidgetSwitcher* ws_SessionUISwitch;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UButton* btn_FindSession;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UScrollBox* sb_RoomListBox;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UButton* btn_CreateSelection;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UButton* btn_FindSelection;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UButton* btn_BackFromCreate;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UButton* btn_BackFromFind;

	UFUNCTION()
	void OnClickCreateButton();

	UFUNCTION()
	void OnClickedCreateSelection();

	UFUNCTION()
	void OnClickedFindSelection();

	UFUNCTION()
	void OnClickFindButton();

	UFUNCTION()
	void ChangeButtonActivation(bool bIsActivation);

	UFUNCTION()
	void BackToFirstCanvas();

	void SwitchCanvas(int32 index);
	UPROPERTY()
	class UH_OverGameInstance* ogi;

	UFUNCTION()
	void AddRoomSlot(struct FSessionSlotInfo slotInfo);

	UPROPERTY()
	class UH_SessionInfoWidget* sessionSlot;

	UPROPERTY(EditAnywhere, Category=MySettings)
	TSubclassOf<class UH_SessionInfoWidget> sessionInfoWidget;
public:
};
