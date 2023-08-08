// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EO_Plate.generated.h"

UCLASS()
class OVERKASE_API AEO_Plate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEO_Plate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* meshComp;
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* sceneComp;

private:
	UPROPERTY(VisibleAnywhere, Category="CompleteFood")
	TSubclassOf<class AEO_CucumberSushi> cucumberSushi;
	UPROPERTY(VisibleAnywhere, Category="CompleteFood")
	TSubclassOf<class AEO_FishSushi> fishSushi;
	UPROPERTY(VisibleAnywhere, Category="CompleteFood")
	TSubclassOf<class AEO_OctopusSushi> octopusSushi;

private:
	UPROPERTY(VisibleAnywhere, Category="Recipe")
	bool bIsRice = false;
	UPROPERTY(VisibleAnywhere, Category="Recipe")
	bool bIsSeaweed = false;
	UPROPERTY(VisibleAnywhere, Category="Recipe")
	bool bIsCucumber = false;
	UPROPERTY(VisibleAnywhere, Category="Recipe")
	bool bIsFish = false;
	UPROPERTY(VisibleAnywhere, Category="Recipe")
	bool bIsOctopus = false;

public:
	UPROPERTY(VisibleAnywhere, Category="Recipe")
	bool bIsComplete = false;
	
	UPROPERTY(VisibleAnywhere, Category="Check")
	bool bDirty = false;

public:
	void MakeCompleteFood();
	UFUNCTION()
	void CheckRecipe(FName foodTag);
};
