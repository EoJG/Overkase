// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_Progressbar.h"
#include <UMG/Public/Components/ProgressBar.h>

void UEO_Progressbar::NativeOnInitialized()
{
	Super::NativeOnInitialized();

}

void UEO_Progressbar::NativeConstruct()
{
	Super::NativeConstruct();
	
}

void UEO_Progressbar::BindProgressFunc()
{
	float percent = curTime / coolTime;

	progressBar->SetPercent(percent);
}
