// Fill out your copyright notice in the Description page of Project Settings.


#include "H_OverkaseCharacter.h"
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h>
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h>
#include "H_OverkaseInteraction.h"
#include "H_OverkasePlayerMove.h"
#include <Components/BoxComponent.h>
#include <Components/SphereComponent.h>
#include "InputMappingContext.h"
#include "EO_AnimationComponent.h"
#include "EO_InGameInterface.h"
#include <Kismet/GameplayStatics.h>
#include "Particles/ParticleSystem.h"
#include <UMG/Public/Blueprint/WidgetBlueprintLibrary.h>
#include "Net/UnrealNetwork.h"
#include "EO_Camera.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "TimerManager.h"
#include "Components/AudioComponent.h"

// Sets default values
AH_OverkaseCharacter::AH_OverkaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	handR = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HandR"));
	handR->SetupAttachment(RootComponent);
	handR->SetRelativeLocationAndRotation(FVector(0, 0, -60), FRotator( 0.000000, -90.000000, 0.000000));

	ConstructorHelpers::FObjectFinder<UStaticMesh>TempHandRMesh(TEXT("/Script/Engine.StaticMesh'/Game/Models/Character/NewFolder/Crocodile_Hand_Open_R.Crocodile_Hand_Open_R'"));

	if (TempHandRMesh.Succeeded()) {
		handR->SetStaticMesh(TempHandRMesh.Object);
	}

	handL = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("handL"));
	handL->SetupAttachment(RootComponent);
	handL->SetRelativeLocationAndRotation(FVector(0, 0, -60), FRotator(0.000000, -90.000000, 0.000000));

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
	interactionPosition->SetRelativeLocation(FVector(0, 100, 70));

	interationDistance = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionDistance"));
	interationDistance->SetupAttachment(crocodileMesh);
	//interationDistance->SetBoxExtent(FVector(80, 70, 50));
	interationDistance->SetSphereRadius(100);
	interationDistance->SetRelativeLocation(FVector(0, 60.000000, 70));
	interationDistance->SetCollisionProfileName(TEXT("Interaction"));

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

	bReplicates = true;

	// 서버부터는 플레이어가 각자 UI를 생성하여야 하여 추가함
	ConstructorHelpers::FClassFinder<UEO_InGameInterface> inUITemp(TEXT("'/Game/Eo/Blueprints/UI/BP_UI_InGameInterface.BP_UI_InGameInterface_C'"));
	if (inUITemp.Succeeded())
	{
		inGameUIClass = inUITemp.Class;
	}
	
	ConstructorHelpers::FObjectFinder<UParticleSystem> TempPart(TEXT("/Script/Engine.ParticleSystem'/Game/HanSeunghui/Effect/P_Explosion.P_Explosion'"));

	if (TempPart.Succeeded())
	{
		effect = TempPart.Object;
	}

	ConstructorHelpers::FObjectFinder<USoundBase> TempSound(TEXT("/Script/Engine.SoundWave'/Game/HanSeunghui/Sound/Dash1.Dash1'"));
	if (TempSound.Succeeded())
	{
		dashSound = TempSound.Object;
	}

	ConstructorHelpers::FObjectFinder<USoundBase> TempPick(TEXT("/Script/Engine.SoundWave'/Game/HanSeunghui/Sound/Item_PickUp_02.Item_PickUp_02'"));
	if (TempPick.Succeeded())
	{
		pickUpSound = TempPick.Object;
	}

	ConstructorHelpers::FObjectFinder<USoundBase> TempPut(TEXT("/Script/Engine.SoundWave'/Game/HanSeunghui/Sound/Item_PutDown_01.Item_PutDown_01'"));
	if (TempPut.Succeeded())
	{
		putDownSound = TempPut.Object;
	}
	ConstructorHelpers::FObjectFinder<USoundBase> TempThrow(TEXT("/Script/Engine.SoundWave'/Game/HanSeunghui/Sound/Throw1.Throw1'"));
	if (TempThrow.Succeeded())
	{
		throwSound = TempThrow.Object;
	}
	ConstructorHelpers::FObjectFinder<USoundBase> TempChop(TEXT("/Script/Engine.SoundWave'/Game/HanSeunghui/Sound/KnifeChop.KnifeChop'"));
	if (TempChop.Succeeded())
	{
		chopSound = TempChop.Object;
	}


	// Niagara 컴포넌트 생성
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));

	// Niagara 에셋 할당
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraSystemAsset(TEXT("/Script/Niagara.NiagaraSystem'/Game/HanSeunghui/Effect/Blast_Particle.Blast_Particle'"));
	if (NiagaraSystemAsset.Succeeded())
	{
		NiagaraComponent->SetAsset(NiagaraSystemAsset.Object);
	}

	// Niagara 컴포넌트를 액터에 부착
	NiagaraComponent->SetupAttachment(crocodileMesh);
	NiagaraComponent->SetRelativeLocation(FVector(0, -60, 0));
	//NiagaraComponent->ActivateSystem(false);
}

void AH_OverkaseCharacter::SendMulticast_Implementation(int32 random)
{
	UE_LOG(LogTemp, Warning, TEXT("SendMulticast_Implementation and NetMode : %d"), GetNetMode());
	inGameUI->SpawnMenu(random);
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

	AActor* cam = nullptr;
	cam = UGameplayStatics::GetActorOfClass(GetWorld(), ACameraActor::StaticClass());
	if (cam != nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("Set camera"));
		GetWorld()->GetFirstPlayerController()->SetViewTarget(cam);
	}

	inGameUI = CreateWidget<UEO_InGameInterface>(GetWorld(), inGameUIClass);
	inGameUI->AddToViewport();

	eoCam = Cast<AEO_Camera>(UGameplayStatics::GetActorOfClass(GetWorld(), AEO_Camera::StaticClass()));

	NiagaraComponent->SetVisibility(false);

}

// Called every frame
void AH_OverkaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	
	//DrawDebugSphere(GetWorld(), GetActorLocation(), 100, 20, FColor::Yellow, false, -1, 0, 2);
	if(HasAuthority())
	{
		if(GetLocalRole() == ROLE_Authority && GetRemoteRole() == ROLE_AutonomousProxy)
		{
			currentTime += DeltaTime;
			if(currentTime >= 5)
			{
				//ServerTestFunc();
				inGameUI->ServerSpawnMenu();
				currentTime = 0;
			}
		}
	}

	if(GetWorld()->GetFirstPlayerController() != GetController())
	{
		if (inGameUI->curTime < 0)
		{
			//UE_LOG(LogTemp, Warning, TEXT("%f"), inGameUI->progress_Timer->GetPercent());
			GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend(eoCam, 2.0f);

			travelTime += DeltaTime;
			//GetWorld()->ServerTravel(TEXT("/Game/Maps/EO_UI"));
			if (travelTime > 5)
			{
				GetWorld()->ServerTravel(TEXT("/Game/Maps/EO_UI"));
				//ServerTravelUI();
				travelTime = 0;
			}
			
		}
	}

	//UE_LOG(LogTemp,Warning,TEXT("%s"),HasAuthority()?TEXT("Authority"):TEXT("Remote"));
}

// Called to bind functionality to input
void AH_OverkaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//델리게이트 한번 호출
	onInputBindingDelegate.Broadcast(PlayerInputComponent);
}

void AH_OverkaseCharacter::MulticastOnParticle_Implementation()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), effect,GetActorLocation(), GetActorRotation(), FVector(0.3f));
}

void AH_OverkaseCharacter::MulticastOnVFX_Implementation()
{
	UE_LOG(LogTemp,Warning,TEXT("VFX"));
	NiagaraComponent->SetVisibility(true);

	/*FString NiagaraAssetPath = TEXT("/Game/HanSeunghui/Effect/Blast_Particle");

	UNiagaraSystem* NiagaraSystem = LoadObject<UNiagaraSystem>(nullptr, *NiagaraAssetPath);

	if (NiagaraSystem)
	{
		UNiagaraComponent* NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NiagaraSystem, GetActorLocation(), GetActorRotation());

		if (NiagaraComponent)
		{
			FTimerHandle TimerHandle;
			float DelayInSeconds = 0.3f;
			GetWorldTimerManager().SetTimer(TimerHandle, [NiagaraComponent]() {
				if (NiagaraComponent)
				{
					NiagaraComponent->Deactivate();
					NiagaraComponent->DestroyComponent();
				}
			}, DelayInSeconds, false);
		}
	}*/
	
}

void AH_OverkaseCharacter::ServerEndVFX_Implementation()
{
	MulticastEndVFX();
}

void AH_OverkaseCharacter::MulticastEndVFX_Implementation()
{
	NiagaraComponent->SetVisibility(false);
}

void AH_OverkaseCharacter::MulticastOnDashSound_Implementation()
{
	UGameplayStatics::PlaySound2D(GetWorld(), dashSound);
}

void AH_OverkaseCharacter::MulticastOnPickUpSound_Implementation()
{
	UGameplayStatics::PlaySound2D(GetWorld(), pickUpSound);
}


void AH_OverkaseCharacter::MulticastOnPutDownSound_Implementation()
{
	UGameplayStatics::PlaySound2D(GetWorld(), putDownSound);
}

void AH_OverkaseCharacter::MulticastOnThrowSound_Implementation()
{
	UGameplayStatics::PlaySound2D(GetWorld(), throwSound);
}

void AH_OverkaseCharacter::MulticastOnChopSound_Implementation()
{
	bSoundPlay = true;

	UAudioComponent* AudioComp = UGameplayStatics::SpawnSound2D(this, chopSound);
	FTimerHandle soundTimerHandle;
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();

	TimerManager.SetTimer(soundTimerHandle, [this, AudioComp]()
		{
			AudioComp->Stop();
			bSoundPlay = false;
		}, 0.2f, false);
}


void AH_OverkaseCharacter::MulticastAddScore_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("MulticastAddScore"));

	inGameUI->AddScore();
}

void AH_OverkaseCharacter::MulticastTestFunc_Implementation(FName foodTag)
{
	 inGameUI->SubmitMenu(foodTag);
}


void AH_OverkaseCharacter::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AH_OverkaseCharacter, currentTime);
	DOREPLIFETIME(AH_OverkaseCharacter, travelTime);
}

