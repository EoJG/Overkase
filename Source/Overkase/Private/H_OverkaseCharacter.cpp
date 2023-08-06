// Fill out your copyright notice in the Description page of Project Settings.


#include "H_OverkaseCharacter.h"
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h>
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h>
#include "H_OverkaseInteraction.h"
#include "H_OverkasePlayerMove.h"
#include <Components/SphereComponent.h>

// Sets default values
AH_OverkaseCharacter::AH_OverkaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	crocodileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Crocodile"));
	crocodileMesh->SetupAttachment(RootComponent);
	crocodileMesh->SetRelativeLocationAndRotation(FVector(0, 0, -60), FRotator(0, -90, 0));

	ConstructorHelpers::FObjectFinder<UStaticMesh>TempCrocoMesh(TEXT("/Script/Engine.StaticMesh'/Game/Models/Character/crocodile.crocodile'"));

	if (TempCrocoMesh.Succeeded()) {
		crocodileMesh->SetStaticMesh(TempCrocoMesh.Object);
	}

	interactionPosition = CreateDefaultSubobject<USceneComponent>(TEXT("InteractionPosition"));
	interactionPosition->SetupAttachment(crocodileMesh);
	interactionPosition->SetRelativeLocation(FVector(160, 0, 0));

	interationDistance = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionDistance"));
	interationDistance->SetupAttachment(crocodileMesh);
	interationDistance->SetRelativeLocation(FVector(0, 160, 60));
	interationDistance->SetSphereRadius(130);
	interationDistance->SetCollisionProfileName(TEXT("PlayerSphereRadius"));

	overPlayerMove = CreateDefaultSubobject<UH_OverkasePlayerMove>(TEXT("PlayerMove"));
	overPlayerInteraction = CreateDefaultSubobject<UH_OverkaseInteraction>(TEXT("PlayerInteraction"));
}

// Called when the game starts or when spawned
void AH_OverkaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//우리가 IMC 를 사용한다고 등록
	auto pc = Cast<APlayerController>(GetController());
	if (pc) {
		auto subSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());
		if (subSystem) {
			subSystem->AddMappingContext(imc, 0);
		}
	}
}

// Called every frame
void AH_OverkaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugSphere(GetWorld(), GetActorLocation(), 100, 20, FColor::Yellow, false, -1, 0, 2);

}

// Called to bind functionality to input
void AH_OverkaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//델리게이트 한번 호출
	onInputBindingDelegate.Broadcast(PlayerInputComponent);

}

