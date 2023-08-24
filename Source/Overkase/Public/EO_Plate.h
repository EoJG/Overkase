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
	AEO_Plate();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* boxComp;
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* meshComp;
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* changeMeshComp;
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* sceneComp;

private:
	UPROPERTY(VisibleAnywhere, Category = "MiddleFood")
	TSubclassOf<class AEO_Food> riceCucumber;
	UPROPERTY(VisibleAnywhere, Category = "MiddleFood")
	TSubclassOf<class AEO_Food> riceFish;
	UPROPERTY(VisibleAnywhere, Category = "MiddleFood")
	TSubclassOf<class AEO_Food> seaweedCucumber;
	UPROPERTY(VisibleAnywhere, Category = "MiddleFood")
	TSubclassOf<class AEO_Food> seaweedFish;
	UPROPERTY(VisibleAnywhere, Category = "MiddleFood")
	TSubclassOf<class AEO_Food> seaweedRice;
	UPROPERTY(VisibleAnywhere, Category = "CompleteFood")
	TSubclassOf<class AEO_Food> cucumberSushi;
	UPROPERTY(VisibleAnywhere, Category = "CompleteFood")
	TSubclassOf<class AEO_Food> fishSushi;
	UPROPERTY(VisibleAnywhere, Category = "CompleteFood")
	TSubclassOf<class AEO_Food> octopusSushi;

private:
	UPROPERTY(VisibleAnywhere, Category = "Recipe")
	bool bIsRice = false;
	UPROPERTY(VisibleAnywhere, Category = "Recipe")
	bool bIsSeaweed = false;
	UPROPERTY(VisibleAnywhere, Category = "Recipe")
	bool bIsCucumber = false;
	UPROPERTY(VisibleAnywhere, Category = "Recipe")
	bool bIsFish = false;
	UPROPERTY(VisibleAnywhere, Category = "Recipe")
	bool bIsOctopus = false;

public:
	UPROPERTY(VisibleAnywhere, Category = "Recipe")
	bool bIsComplete = false;

	UPROPERTY(VisibleAnywhere, Category = "Check")
	bool bDirty = false;

public:
	void MakeCompleteFood();
	UFUNCTION()
	void CheckRecipe(FName foodTag);
	UFUNCTION()
	bool CheckOnFood(FName foodTag);

	UFUNCTION()
	void ReplateFood(TArray<AActor*> foods, TSubclassOf<class AEO_Food> spawnFood);
};
