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
#include "Components/TextBlock.h"
#include "Components/CapsuleComponent.h"
#include "H_LerpCameraActor.h"
#include <UMG/Public/Components/Border.h>

// Sets default values
AH_OverkaseCharacter::AH_OverkaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));

	handR = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HandR"));
	handR->SetupAttachment(RootComponent);
	handR->SetRelativeLocationAndRotation(FVector(0, 0, -60), FRotator( 0.000000, -90.000000, 0.000000));
	handR->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ConstructorHelpers::FObjectFinder<UStaticMesh>TempHandRMesh(TEXT("/Script/Engine.StaticMesh'/Game/Models/Character/NewFolder/Crocodile_Hand_Open_R.Crocodile_Hand_Open_R'"));

	if (TempHandRMesh.Succeeded()) {
		handR->SetStaticMesh(TempHandRMesh.Object);
	}

	handL = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("handL"));
	handL->SetupAttachment(RootComponent);
	handL->SetRelativeLocationAndRotation(FVector(0, 0, -60), FRotator(0.000000, -90.000000, 0.000000));
	handL->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ConstructorHelpers::FObjectFinder<UStaticMesh>TempHandLMesh(TEXT("/Script/Engine.StaticMesh'/Game/Models/Character/NewFolder/Crocodile_Hand_Open_L.Crocodile_Hand_Open_L'"));

	if (TempHandLMesh.Succeeded()) {
		handL->SetStaticMesh(TempHandLMesh.Object);
	}
	
	crocodileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Crocodile"));
	crocodileMesh->SetupAttachment(RootComponent);
	crocodileMesh->SetRelativeLocationAndRotation(FVector(0, 0, -60), FRotator(0, -90, 0));
	crocodileMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ConstructorHelpers::FObjectFinder<UStaticMesh>TempCrocoMesh(TEXT("/Script/Engine.StaticMesh'/Game/Models/Character/NewFolder/Body.Body'"));

	if (TempCrocoMesh.Succeeded()) {
		crocodileMesh->SetStaticMesh(TempCrocoMesh.Object);
	}

	headComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Head"));
	headComp->SetupAttachment(crocodileMesh);
	headComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);


	ConstructorHelpers::FObjectFinder<UStaticMesh>TempHeadMesh(TEXT("/Script/Engine.StaticMesh'/Game/Models/Character/NewFolder/Chef_Crocodile_Chef_Crocodile.Chef_Crocodile_Chef_Crocodile'"));

	if (TempHeadMesh.Succeeded()) {
		headComp->SetStaticMesh(TempHeadMesh.Object);
	}

	hatComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hat"));
	hatComp->SetupAttachment(headComp);
	hatComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);


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
	interationDistance->SetSphereRadius(50);
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
	ConstructorHelpers::FObjectFinder<USoundBase> TempCatch1(TEXT("/Script/Engine.SoundWave'/Game/HanSeunghui/BetaSound/Catch1.Catch1'"));
	if (TempCatch1.Succeeded())
	{
		catchSound = TempCatch1.Object;
	}
	ConstructorHelpers::FObjectFinder<USoundBase> TempBGM1(TEXT("/Script/Engine.SoundWave'/Game/HanSeunghui/Sound/y2mate_com-Overcooked-2-Soundtrack-Sushi-City.y2mate_com-Overcooked-2-Soundtrack-Sushi-City'"));
	if (TempBGM1.Succeeded())
	{
		BGMSound = TempBGM1.Object;
	}
	ConstructorHelpers::FObjectFinder<USoundBase> TempEnding(TEXT("/Script/Engine.SoundWave'/Game/HanSeunghui/BetaSound/CityLiving.CityLiving'"));
	if (TempEnding.Succeeded())
	{
		endingSound = TempEnding.Object;
	}
	ConstructorHelpers::FObjectFinder<USoundBase> TempTimeOut(TEXT("/Script/Engine.SoundWave'/Game/HanSeunghui/BetaSound/TimesUpSting.TimesUpSting'"));
	if (TempTimeOut.Succeeded())
	{
		timeOutSound = TempTimeOut.Object;
	}
	// Niagara 컴포넌트 생성
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));

	// Niagara 에셋 할당
	/*static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraSystemAsset(TEXT("/Script/Niagara.NiagaraSystem'/Game/HanSeunghui/Effect/Blast_Particle.Blast_Particle'"));
	if (NiagaraSystemAsset.Succeeded())
	{
		NiagaraComponent->SetAsset(NiagaraSystemAsset.Object);
	}*/

	// Niagara 컴포넌트를 액터에 부착
	NiagaraComponent->SetupAttachment(crocodileMesh);
	NiagaraComponent->SetRelativeLocation(FVector(0, -60, 20));
	NiagaraComponent->ActivateSystem(true);

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

	//NiagaraComponent->ActivateSystem(true);

	walkEffect = LoadObject<UNiagaraSystem>(nullptr, TEXT("/Script/Niagara.NiagaraSystem'/Game/HanSeunghui/Effect/Blast_Particle_walk.Blast_Particle_walk'"));
	dashEffect = LoadObject<UNiagaraSystem>(nullptr, TEXT("/Script/Niagara.NiagaraSystem'/Game/HanSeunghui/Effect/Blast_Particle.Blast_Particle'"));

	NiagaraComponent->SetAsset(walkEffect);
	NiagaraComponent->SetVisibility(true);
	//GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Green, FString::Printf(TEXT("%s"),)

	BGMAudio = UGameplayStatics::SpawnSound2D(GetWorld(), BGMSound);

	UE_LOG(LogTemp, Warning, TEXT("%s"),*GetWorld()->GetFirstPlayerController()->GetCharacter()->GetName());
	if (GetLocalRole() == ROLE_Authority)
	{
		if(GetRemoteRole() == ROLE_AutonomousProxy)
		{
			inGameUI = CreateWidget<UEO_InGameInterface>(GetWorld(), inGameUIClass);
			inGameUI->AddToViewport();
		}
	}
	else if (GetLocalRole() == ROLE_AutonomousProxy)
	{
		inGameUI = CreateWidget<UEO_InGameInterface>(GetWorld(), inGameUIClass);
		inGameUI->AddToViewport();
	}

	inGameUI = CreateWidget<UEO_InGameInterface>(GetWorld(), inGameUIClass);
	inGameUI->AddToViewport();

	//SetTargetCamera();
	AActor* cam = nullptr;
	cam = UGameplayStatics::GetActorOfClass(GetWorld(), ACameraActor::StaticClass());
	if (cam != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *GetWorld()->GetFirstPlayerController()->GetCharacter()->GetName());
		GetWorld()->GetFirstPlayerController()->SetViewTarget(cam);
	}

	h_main_cam = Cast<AH_LerpCameraActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AH_LerpCameraActor::StaticClass()));
	mainCam = UGameplayStatics::GetActorOfClass(GetWorld(), ACameraActor::StaticClass());
	eoCam = Cast<AEO_Camera>(UGameplayStatics::GetActorOfClass(GetWorld(), AEO_Camera::StaticClass()));
	//NiagaraComponent->SetIsReplicated(true);
	//NiagaraComponent->SetVisibility(false);
}

// Called every frame
void AH_OverkaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(IsValid(inGameUI))
	{
		if (inGameUI->curTime < 1)
		{
			if (!bTimeOutPlay)
			{
				TimeOutSound();
			}
		}

		if (inGameUI->curTime < 0)
		{
			if (BGMAudio)
			{
				BGMAudio->Stop();
			}
			if (!bEndingplay)
			{
				EndingSound();
			}
		}
	}

	if (h_main_cam != nullptr && GetWorld()->GetFirstPlayerController()->GetViewTarget() != h_main_cam)
	{
		GetWorld()->GetFirstPlayerController()->SetViewTarget(h_main_cam);
		h_main_cam = nullptr;
	}
	
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
			inGameUI->ws_InGameSwitcher->SetActiveWidgetIndex(1);
			GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend(eoCam, 2.0f);

			/*travelTime += DeltaTime;
			if (travelTime > 5)
			{
				GetWorld()->ServerTravel(TEXT("/Game/Maps/EO_UI"));
				travelTime = 0;
			}*/
			if (inGameUI->talkCount == 0)
			{
				inGameUI->text_human1->SetVisibility(ESlateVisibility::Visible);
				inGameUI->SetWriteText(FString::Printf(TEXT("짧은 시간 동안 훌륭한 요리 솜씨를 보여주었군요! 그러나 이제부터가 시작입니다, 쉐프.")));
			}
			else if (inGameUI->talkCount == 1)
			{
				inGameUI->text_human1->SetVisibility(ESlateVisibility::Hidden);
				inGameUI->text_human2->SetVisibility(ESlateVisibility::Visible);
				inGameUI->SetWriteText(FString::Printf(TEXT("당신들은 좀 더 숙련된 협동력을 보여주어야 우리들의 입맛을 제대로 충족시킬 수 있습니다.")));
			}
			else if (inGameUI->talkCount == 2)
			{
				inGameUI->text_human1->SetVisibility(ESlateVisibility::Visible);
				inGameUI->text_human2->SetVisibility(ESlateVisibility::Hidden);
				inGameUI->SetWriteText(FString::Printf(TEXT("이제 도시를 벗어나 야생의 땅으로 향하는 건 어때요? 그곳에는 어떤 대식가든 만족시킬 수 있는 맛들이 있다고 들었어요!")));
			}
			else if (inGameUI->talkCount == 3)
			{
				inGameUI->text_human1->SetVisibility(ESlateVisibility::Hidden);
				inGameUI->text_human2->SetVisibility(ESlateVisibility::Visible);
				inGameUI->SetWriteText(FString::Printf(TEXT("이제 가야 할 시간이군요. 다음에 우리가 찾아올땐 더욱 달달한 팀워크를 이루길 빌어요.")));
			}

			inGameUI->WrtingText();
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
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), effect, GetActorLocation(), GetActorRotation(), FVector(0.3f));
}

void AH_OverkaseCharacter::MulticastOnVFX_Implementation()
{
	//UE_LOG(LogTemp,Warning,TEXT("VFX"));
	//NiagaraComponent->SetVisibility(true);

	if (NiagaraComponent)
	{
		// Niagara 컴포넌트에 시스템 설정
		NiagaraComponent->SetAsset(dashEffect);
		//GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Black, FString::Printf(TEXT("%s"), *NiagaraComponent->GetAsset()->GetName()));

		NiagaraComponent->ResetSystem();
	}

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
	UE_LOG(LogTemp, Warning, TEXT("ServerEndVFX"));

	MulticastEndVFX();
	

}

void AH_OverkaseCharacter::MulticastEndVFX_Implementation()
{
	//UE_LOG(LogTemp,Warning,TEXT("%s"), *GetOwner()->GetName());
	//NiagaraComponent->SetVisibility(false);
	if (NiagaraComponent)
	{
		// Niagara 컴포넌트에 시스템 설정
		NiagaraComponent->SetAsset(walkEffect);
		NiagaraComponent->ResetSystem();

		//GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Black, FString::Printf(TEXT("%s"), *NiagaraComponent->GetAsset()->GetName()));
	}
	/*if (HasAuthority()) {
	}*/
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


void AH_OverkaseCharacter::ServerOnCatchSound_Implementation()
{
	MulticastOnCatchSound();
}

void AH_OverkaseCharacter::MulticastOnCatchSound_Implementation()
{
	UGameplayStatics::PlaySound2D(GetWorld(), catchSound);
}


void AH_OverkaseCharacter::MulticastAddScore_Implementation(int score)
{
	UE_LOG(LogTemp, Warning, TEXT("MulticastAddScore"));
	UE_LOG(LogTemp, Warning, TEXT("Player: %s"), *GetName());

	//inGameUI->AddScore();
	/*int random = FMath::RandRange(1, 4);
	int plusPoint = 0;

	switch (random)
	{
	case 1:
		plusPoint = 5;
		break;
	case 2:
		plusPoint = 6;
		break;
	case 3:
		plusPoint = 7;
		break;
	case 4:
		plusPoint = 8;
		break;
	}*/

	inGameUI->score += 60 + score;
	inGameUI->text_Score->SetText(FText::AsNumber(inGameUI->score));
	/*score += 60 + plusPoint;
	text_Score->SetText(FText::AsNumber(score));*/	
}

void AH_OverkaseCharacter::MulticastTestFunc_Implementation(FName foodTag)
{
	 inGameUI->SubmitMenu(foodTag);
}

void AH_OverkaseCharacter::TimeOutSound()
{
	bTimeOutPlay = true;
	UGameplayStatics::PlaySound2D(GetWorld(), timeOutSound);
}

void AH_OverkaseCharacter::EndingSound()
{
	UGameplayStatics::PlaySound2D(GetWorld(), endingSound);
	bEndingplay = true;
}

void AH_OverkaseCharacter::ServerAddScore_Implementation()
{
	//여기서 점수 먹이고 넘겨야함
	int random = FMath::RandRange(1, 4);
	int plusPoint = 0;

	switch (random)
	{
	case 1:
		plusPoint = 5;
		break;
	case 2:
		plusPoint = 6;
		break;
	case 3:
		plusPoint = 7;
		break;
	case 4:
		plusPoint = 8;
		break;
	}

	MulticastAddScore(plusPoint);
}

void AH_OverkaseCharacter::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AH_OverkaseCharacter, currentTime);
	DOREPLIFETIME(AH_OverkaseCharacter, travelTime);
}

