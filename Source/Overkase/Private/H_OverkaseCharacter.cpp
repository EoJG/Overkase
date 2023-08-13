// Fill out your copyright notice in the Description page of Project Settings.


#include "H_OverkaseCharacter.h"
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h>
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h>
#include "H_OverkaseInteraction.h"
#include "H_OverkasePlayerMove.h"
#include <Components/BoxComponent.h>
#include <Components/SphereComponent.h>
#include "InputMappingContext.h"

// Sets default values
AH_OverkaseCharacter::AH_OverkaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	handComp = CreateDefaultSubobject<USceneComponent>(TEXT("Hand"));
	handComp->SetupAttachment(RootComponent);
	handComp->SetRelativeLocation(FVector(0,0,-60));

	handRComp = CreateDefaultSubobject<USceneComponent>(TEXT("HandRComp"));
	handRComp->SetupAttachment(handComp);
	handRComp->SetRelativeLocation(FVector(0,0,90));

	handR = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HandR"));
	handR->SetupAttachment(handRComp);
	handR->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator( 0.000000, -90.000000, 0.000000));

	ConstructorHelpers::FObjectFinder<UStaticMesh>TempHandRMesh(TEXT("/Script/Engine.StaticMesh'/Game/Models/Character/NewFolder/Crocodile_Hand_Open_R.Crocodile_Hand_Open_R'"));

	if (TempHandRMesh.Succeeded()) {
		handR->SetStaticMesh(TempHandRMesh.Object);
	}

	handL = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("handL"));
	handL->SetupAttachment(handComp);
	handL->SetRelativeLocationAndRotation(FVector(0, 0, 0), FRotator(0.000000, -90.000000, 0.000000));

	ConstructorHelpers::FObjectFinder<UStaticMesh>TempHandLMesh(TEXT("/Script/Engine.StaticMesh'/Game/Models/Character/NewFolder/Crocodile_Hand_Open_L.Crocodile_Hand_Open_L'"));

	if (TempHandLMesh.Succeeded()) {
		handL->SetStaticMesh(TempHandLMesh.Object);
	}

	crocodileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Crocodile"));
	crocodileMesh->SetupAttachment(RootComponent);
	crocodileMesh->SetRelativeLocationAndRotation(FVector(0, 0, -60), FRotator(0, -90, 0));

	ConstructorHelpers::FObjectFinder<UStaticMesh>TempCrocoMesh(TEXT("/Script/Engine.StaticMesh'/Game/Models/Character/NewFolder/Body.Body'"));

	if (TempCrocoMesh.Succeeded()) {
		crocodileMesh->SetStaticMesh(TempCrocoMesh.Object);
	}

	headComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Head"));
	headComp->SetupAttachment(crocodileMesh);

	ConstructorHelpers::FObjectFinder<UStaticMesh>TempHeadMesh(TEXT("/Script/Engine.StaticMesh'/Game/Models/Character/NewFolder/Chef_Crocodile_Chef_Crocodile.Chef_Crocodile_Chef_Crocodile'"));

	if (TempHeadMesh.Succeeded()) {
		headComp->SetStaticMesh(TempHeadMesh.Object);
	}

	hatComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hat"));
	hatComp->SetupAttachment(headComp);

	ConstructorHelpers::FObjectFinder<UStaticMesh>TempHatMesh(TEXT("/Script/Engine.StaticMesh'/Game/Models/Character/NewFolder/Chef_Crocodile_SubMesh_0.Chef_Crocodile_SubMesh_0'"));

	if (TempHatMesh.Succeeded()) {
		hatComp->SetStaticMesh(TempHatMesh.Object);
	}



	interactionPosition = CreateDefaultSubobject<USceneComponent>(TEXT("InteractionPosition"));
	interactionPosition->SetupAttachment(crocodileMesh);
	interactionPosition->SetRelativeLocation(FVector(160, 0, 0));

	interationDistance = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionDistance"));
	interationDistance->SetupAttachment(crocodileMesh);
	//interationDistance->SetBoxExtent(FVector(80, 70, 50));
	interationDistance->SetSphereRadius(100);
	interationDistance->SetRelativeLocation(FVector(0, 60.000000, 70));
	interationDistance->SetCollisionProfileName(TEXT("InteractionDistance"));

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	overPlayerMove = CreateDefaultSubobject<UH_OverkasePlayerMove>(TEXT("PlayerMove"));
	overPlayerInteraction = CreateDefaultSubobject<UH_OverkaseInteraction>(TEXT("PlayerInteraction"));

	ConstructorHelpers::FObjectFinder<UInputMappingContext> TempIMC(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/HanSeunghui/Input/IMC_OverkaseInput.IMC_OverkaseInput'"));
	if (TempIMC.Succeeded())
	{
		imc = TempIMC.Object;
	}
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

	//DrawDebugSphere(GetWorld(), GetActorLocation(), 100, 20, FColor::Yellow, false, -1, 0, 2);

}

// Called to bind functionality to input
void AH_OverkaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//델리게이트 한번 호출
	onInputBindingDelegate.Broadcast(PlayerInputComponent);

}

