// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Mooner_sushi.generated.h"

UCLASS()
class OVERKASE_API AMooner_sushi : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMooner_sushi();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
