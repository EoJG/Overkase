// Fill out your copyright notice in the Description page of Project Settings.


#include "H_LerpCameraActor.h"
#include <Kismet/GameplayStatics.h>
#include "H_OverkaseCharacter.h"
#include <GameFramework/SpringArmComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Camera/CameraComponent.h>
#include <Engine/Engine.h>

// Sets default values
AH_LerpCameraActor::AH_LerpCameraActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(meshComp);

	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	springArm->SetupAttachment(meshComp);
	springArm->TargetArmLength = targetArmLength;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Cam"));
	CameraComp->SetupAttachment(springArm);

	springArm->SetIsReplicated(true);
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

	FVector lerpLoc = FMath::Lerp(GetActorLocation(), avgLoc, 0.01f);

	if (avgLoc.X < -720.0f && avgLoc.X > -1200.0f && avgLoc.Y < 420.0f && avgLoc.Y > -100.0f)
	{
		SetActorLocation(lerpLoc);
	}


	if (PlayerActors.Num() >= 2)
	{
		float dist = FVector::Dist(PlayerActors[0]->GetActorLocation(), PlayerActors[1]->GetActorLocation());
		//GEngine->AddOnScreenDebugMessage(-1, 0.01f, FColor::Green, FString::Printf(TEXT("%f"), dist));
		if (dist >= 900)
		{

			if (springArm != nullptr)
			{
				if (targetZoomOutLength < 1800)
				{
					float lerpFloat = FMath::Lerp(4, 1, lerpAlpha);
					targetZoomOutLength = targetArmLength += lerpFloat;
					springArm->TargetArmLength = targetZoomOutLength;
					//GEngine->AddOnScreenDebugMessage(-1, 0.01f, FColor::Black, FString::Printf(TEXT("%f"), targetZoomOutLength));

				}
			}
			else { UE_LOG(LogTemp, Warning, TEXT("Nullllllll")); }
		}
		else
		{
			if (springArm != nullptr)
			{
				if (targetZoomOutLength > 1600)
				{
					float lerpFloat2 = FMath::Lerp(4, 1, lerpAlpha);
					targetZoomOutLength = targetArmLength -= lerpFloat2;
					springArm->TargetArmLength = targetZoomOutLength;
				}
			}
		}
	}
}