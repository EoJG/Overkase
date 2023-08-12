// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EO_Progressbar.generated.h"

/**
 * 
 */
UCLASS()
class OVERKASE_API UEO_Progressbar : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized();
	virtual void NativeConstruct();

private:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	class UCanvasPanel* canvasPanel;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	class USizeBox* sizeBox;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	class UProgressBar* progressBar;

public:
	UPROPERTY(VisibleAnywhere)
	class AEO_Block* block;

public:
	UPROPERTY(VisibleAnywhere, Category="Settings")
	float curTime = 0;
	UPROPERTY(VisibleAnywhere, Category="Settings")
	float coolTime = 0;

public:
	UFUNCTION()
	void BindProgressFunc();
};
