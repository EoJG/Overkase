// Fill out your copyright notice in the Description page of Project Settings.


#include "H_LerpCameraActor.h"
#include <Kismet/GameplayStatics.h>
#include "H_OverkaseCharacter.h"
#include <GameFramework/SpringArmComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Camera/CameraComponent.h>

// Sets default values
AH_LerpCameraActor::AH_LerpCameraActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(meshComp);

	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	springArm->SetupAttachment(meshComp);
	springArm->TargetArmLength = 1600;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Cam"));
	CameraComp->SetupAttachment(springArm);

}

// Called when the game starts or when spawned
void AH_LerpCameraActor::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void AH_LerpCameraActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AH_OverkaseCharacter::StaticClass(), PlayerActors);

	FVector avgLoc = UGameplayStatics::GetActorArrayAverageLocation(PlayerActors);

	FVector lerpLoc = FMath::Lerp(GetActorLocation(), avgLoc, 0.1f);

	SetActorLocation(lerpLoc);
}