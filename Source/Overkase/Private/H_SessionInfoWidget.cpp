// Fill out your copyright notice in the Description page of Project Settings.


#include "H_SessionInfoWidget.h"
#include "Components/Button.h"

void UH_SessionInfoWidget::NativeConstruct()
{
	ogi = GetGameInstance<UH_OverGameInstance>();

	btn_Join->OnClicked.AddDynamic(this, &UH_SessionInfoWidget::OnClickedJoinButton);

}

void UH_SessionInfoWidget::OnClickedJoinButton()
{
	if (ogi != nullptr)
	{
		ogi->JoinSelectedSession(sessionIndex);
	}
}
