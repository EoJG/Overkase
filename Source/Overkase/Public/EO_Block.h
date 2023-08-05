// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EO_Block.generated.h"

UCLASS()
class OVERKASE_API AEO_Block : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEO_Block();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* boxComp;
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* meshComp;
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* sceneComp;

	UPROPERTY(VisibleAnywhere)
	TSubclassOf<class AEO_Plate> plate;
	UPROPERTY(VisibleAnywhere)
	TSubclassOf<class AEO_Pot> pot;

public:
	UPROPERTY(VisibleAnywhere, Category="Check")
	bool bOnItem = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Check")
	bool bIsInterObj = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
	bool bSpawnPlate = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
	bool bSpawnPot = false;

public:
	UFUNCTION(BlueprintCallable)
	virtual void OnItem(class AActor* item);
	UFUNCTION(BlueprintCallable)
	virtual void GetItem(class USceneComponent* playerSceneComp);
	UFUNCTION(BlueprintCallable)
	virtual void Interaction();
};
