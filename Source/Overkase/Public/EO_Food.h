// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EO_Food.generated.h"

UCLASS()
class OVERKASE_API AEO_Food : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEO_Food();

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
	class UStaticMeshComponent* changeMeshComp;
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* platedMeshComp;

public:
	UPROPERTY(VisibleAnywhere, Category="Check")
	bool bIsCooked = false;
	UPROPERTY(VisibleAnywhere, Category = "Check")
	bool bIsOrigin = false;
	UPROPERTY(VisibleAnywhere, Category="Check")
	bool bIsComplete = false;

	UPROPERTY(VisibleAnywhere, Category="Recipe")
	bool bCanChop = false;
	UPROPERTY(VisibleAnywhere, Category="Recipe")
	bool bCanBoil = false;

	UPROPERTY(VisibleAnywhere, Category="Recipe")
	float curTime = 0;
	UPROPERTY(VisibleAnywhere, Category="Recipe")
	float coolTime = 0;

public:
	UFUNCTION(BlueprintCallable)
	void ShootFood(FVector forward);

	UFUNCTION(NetMulticast, Reliable)
	void PickUpItem();
	UFUNCTION(NetMulticast, Reliable)
	void DropItem();

	UFUNCTION()
	void FoodVisible();
	UFUNCTION()
	void ChangeVisible();
	UFUNCTION()
	void PlatedVisible();
};
