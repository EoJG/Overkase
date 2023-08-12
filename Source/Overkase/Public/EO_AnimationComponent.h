// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EO_AnimationComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OVERKASE_API UEO_AnimationComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEO_AnimationComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* bodyMesh;
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* headMesh;	
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* handComp;
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* handRComp;
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* handRMesh;	
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* handLMesh;

private:
	bool isPlayChopHand = false;
	bool isPlayWashHand = false;
	bool bDoOnce = true;

	float time = 0;
	float c = 0;

public:
	UFUNCTION(BlueprintCallable)
	void UpHand();
	UFUNCTION(BlueprintCallable)
	void DownHand();
	UFUNCTION(BlueprintCallable)
	void CallChopHand(bool playAnimation);
	UFUNCTION(BlueprintCallable)
	void CallWashHand(bool playAnimation);

private:
	UFUNCTION()
	void ChopHand();
	UFUNCTION()
	void WashHand();
};
