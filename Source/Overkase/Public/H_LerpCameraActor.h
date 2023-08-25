// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "H_LerpCameraActor.generated.h"

UCLASS()
class OVERKASE_API AH_LerpCameraActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AH_LerpCameraActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* meshComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USpringArmComponent* springArm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UCameraComponent* CameraComp;

	TArray<AActor*> PlayerActors;
	TArray<class AH_OverkaseCharacter> overPlayerActors;

	UPROPERTY(EditAnywhere, Category = CameraMoving)
	float targetArmLength = 1400;
	UPROPERTY(EditAnywhere, Category = CameraMoving)
	float targetZoomOutLength = 0;
	UPROPERTY(EditAnywhere, Category = CameraMoving)
	float lerpAlpha = 0.5f;

};
