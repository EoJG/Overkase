// Fill out your copyright notice in the Description page of Project Settings.


#include "H_OverLoginWidget.h"
#include "H_OverGameInstance.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Components/ScrollBox.h"
#include "Components/WidgetSwitcher.h"


void UH_OverLoginWidget::NativeConstruct()
{
	ogi = GetGameInstance<UH_OverGameInstance>();

	btn_CreateSession->OnClicked.AddDynamic(this, &UH_OverLoginWidget::OnClickCreateButton);
	btn_CreateSelection->OnClicked.AddDynamic(this, &UH_OverLoginWidget::OnClickedCreateSelection);
	btn_FindSelection->OnClicked.AddDynamic(this, &UH_OverLoginWidget::OnClickedFindSelection);
	btn_FindSession->OnClicked.AddDynamic(this, &UH_OverLoginWidget::OnClickFindButton);
	btn_BackFromCreate->OnClicked.AddDynamic(this, &UH_OverLoginWidget::BackToFirstCanvas);
	btn_BackFromFind->OnClicked.AddDynamic(this, &UH_OverLoginWidget::BackToFirstCanvas);

	if (ogi != nullptr)
	{
		ogi->onSearchCompleted.AddDynamic(this, &UH_OverLoginWidget::AddRoomSlot);
		ogi->onFindButtonActivation.AddDynamic(this, &UH_OverLoginWidget::ChangeButtonActivation);
	}
}

void UH_OverLoginWidget::OnClickCreateButton()
{
	if (ogi != nullptr && !edit_roomName->GetText().IsEmpty())
	{
		ogi->CreateMySession(edit_roomName->GetText());
	}
}

void UH_OverLoginWidget::OnClickedCreateSelection()
{
	SwitchCanvas(1);

}

void UH_OverLoginWidget::OnClickedFindSelection()
{
	SwitchCanvas(2);
	OnClickFindButton();
}

void UH_OverLoginWidget::OnClickFindButton()
{
	if (ogi != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("OnClickFindButton"));
		ogi->FindOtherSession();
		sb_RoomListBox->ClearChildren();
	}
}

void UH_OverLoginWidget::ChangeButtonActivation(bool bIsActivation)
{
	btn_FindSession->SetIsEnabled(bIsActivation);

}

void UH_OverLoginWidget::BackToFirstCanvas()
{
	ws_SessionUISwitch->SetActiveWidgetIndex(0);

}

void UH_OverLoginWidget::SwitchCanvas(int32 index)
{
	ws_SessionUISwitch->SetActiveWidgetIndex(index);
}

void UH_OverLoginWidget::AddRoomSlot(FSessionSlotInfo slotInfo)
{
	// ���� ������ �����Ѵ�.
	sessionSlot = CreateWidget<UH_SessionInfoWidget>(GetWorld(), sessionInfoWidget);

	if (sessionSlot != nullptr)
	{
		// ���� ������ �� ��ҿ� ���� ������ �ִ´�.
		sessionSlot->text_RoomName->SetText(FText::FromString(slotInfo.roomName));
		sessionSlot->text_HostName->SetText(FText::FromString(slotInfo.hostName));
		sessionSlot->text_PingSpeed->SetText(FText::AsNumber(slotInfo.pingSpeed));
		sessionSlot->sessionIndex = slotInfo.sessionIndex;

		// ������ ���� ������ ��ũ�� �ڽ��� �ڽ����� �߰��Ѵ�.
		sb_RoomListBox->AddChild(sessionSlot);
	}
}
