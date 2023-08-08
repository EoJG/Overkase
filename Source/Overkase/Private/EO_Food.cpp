// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_Food.h"

// Sets default values
AEO_Food::AEO_Food()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEO_Food::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEO_Food::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

