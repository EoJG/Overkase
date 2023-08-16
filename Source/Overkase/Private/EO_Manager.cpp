// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_Manager.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AEO_Manager::AEO_Manager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEO_Manager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEO_Manager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

