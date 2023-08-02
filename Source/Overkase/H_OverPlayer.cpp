// Fill out your copyright notice in the Description page of Project Settings.


#include "H_OverPlayer.h"

// Sets default values
AH_OverPlayer::AH_OverPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AH_OverPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AH_OverPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AH_OverPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

