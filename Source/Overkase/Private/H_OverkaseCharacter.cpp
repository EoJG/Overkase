// Fill out your copyright notice in the Description page of Project Settings.


#include "H_OverkaseCharacter.h"
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h>
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h>
#include "H_OverkaseInteraction.h"
#include "H_OverkasePlayerMove.h"

// Sets default values
AH_OverkaseCharacter::AH_OverkaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	overPlayerMove = CreateDefaultSubobject<UH_OverkasePlayerMove>(TEXT("PlayerMove"));
	overPlayerInteraction = CreateDefaultSubobject<UH_OverkaseInteraction>(TEXT("PlayerInteraction"));
}

// Called when the game starts or when spawned
void AH_OverkaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//�츮�� IMC �� ����Ѵٰ� ���
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

}

// Called to bind functionality to input
void AH_OverkaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//��������Ʈ �ѹ� ȣ��
	onInputBindingDelegate.Broadcast(PlayerInputComponent);

}

