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

public:	
	UPROPERTY(VisibleAnywhere, Category="Check")
	bool bOnItem = false;

public:
	UFUNCTION(BlueprintCallable)
	void OnItem(class AActor* item);
	UFUNCTION(BlueprintCallable)
	virtual void GetItem(class USceneComponent* playerSceneComp);
};
