// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_Food.h"
#include <Components/BoxComponent.h>
#include "EO_Block.h"
#include "H_OverkaseCharacter.h"
#include "H_OverkaseInteraction.h"
#include <Kismet/GameplayStatics.h>
#include "Net/UnrealNetwork.h"

// Sets default values
AEO_Food::AEO_Food()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = boxComp;
	boxComp->SetLinearDamping(2.5f);
	boxComp->BodyInstance.bOverrideMass = true;
	boxComp->BodyInstance.SetMassOverride(20);
	boxComp->BodyInstance.bLockRotation = true;
	boxComp->SetCollisionProfileName(TEXT("Food"));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	meshComp->SetupAttachment(RootComponent);
	meshComp->SetCollisionProfileName(TEXT("NoCollision"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> meshTemp(TEXT("'/Engine/BasicShapes/Sphere.Sphere'"));
	if (meshTemp.Succeeded())
	{
		meshComp->SetStaticMesh(meshTemp.Object);
	}

	changeMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChangeMeshComponent"));
	changeMeshComp->SetupAttachment(RootComponent);
	changeMeshComp->SetCollisionProfileName(TEXT("NoCollision"));
	changeMeshComp->SetVisibility(false);

	platedMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatedMeshComponent"));
	platedMeshComp->SetupAttachment(RootComponent);
	platedMeshComp->SetCollisionProfileName(TEXT("NoCollision"));
	platedMeshComp->SetVisibility(false);

	bReplicates = true;
	SetReplicateMovement(true);
	meshComp->SetIsReplicated(true);
	changeMeshComp->SetIsReplicated(true);
	platedMeshComp->SetIsReplicated(true);
}

// Called when the game starts or when spawned
void AEO_Food::BeginPlay()
{
	Super::BeginPlay();
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AEO_Food::OnComponentBeginOverlap);


}

// Called every frame
void AEO_Food::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); 

	/*ServerCheckOnGround();
	ServerCheckOnHand();*/

	FVector CharacterLocation = GetActorLocation();

	FVector StartPos = CharacterLocation;
	FVector EndPos = CharacterLocation - FVector(0, 0, 20);

	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartPos, EndPos, ECC_Visibility, CollisionParams);

	if (bHit)
	{
		bIsOnGround = true;
	}
	else
	{
		bIsOnGround = false;
	}


	DrawDebugLine(GetWorld(), StartPos, EndPos, FColor::Green, false, -1, 0, 1);


	FVector End1Pos = CharacterLocation + GetActorRightVector() * -100;

	FHitResult Hit1Result;
	FCollisionQueryParams Collision1Params;
	Collision1Params.AddIgnoredActor(this);
	bool b1Hit = GetWorld()->LineTraceSingleByChannel(Hit1Result, StartPos, End1Pos, ECC_Visibility, Collision1Params);

	if (b1Hit)
	{
		bIsOnHand = true;
	}
	else
	{
		bIsOnHand = false;
	}


	DrawDebugLine(GetWorld(), StartPos, End1Pos, FColor::Black, false, -1, 0, 1);
	
}

void AEO_Food::ShootFood(FVector forward)
{
	FVector dir = forward * 30000;

	//UE_LOG(LogTemp, Warning, TEXT("%s"), *boxComp->GetOwner()->GetName());
	boxComp->SetSimulatePhysics(true);
	boxComp->AddImpulse(dir);
}

void AEO_Food::PickUpItem_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("PickUpItem_Implementation, NetMode : %d"), GetNetMode());
	boxComp->SetSimulatePhysics(false);

}

void AEO_Food::DropItem_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("DropItem_Implementation, NetMode : %d"), GetNetMode());
	boxComp->SetSimulatePhysics(true);

}

void AEO_Food::ServerOverlapItemOnBlock_Implementation(USceneComponent* sceneComp)
{
	MulticastOverlapItemOnBlock(sceneComp);
}

void AEO_Food::MulticastOverlapItemOnBlock_Implementation(USceneComponent* sceneComp)
{
	boxComp->SetSimulatePhysics(false);
	this->AttachToComponent(sceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	
}



void AEO_Food::ServerCheckOnHand_Implementation()
{
	MulticastCheckOnHand();
}

void AEO_Food::MulticastCheckOnHand_Implementation()
{
	FVector CharacterLocation = GetActorLocation();

	FVector StartPos = CharacterLocation;
	FVector End1Pos = CharacterLocation + GetActorRightVector() * -100;

	FHitResult Hit1Result;
	FCollisionQueryParams Collision1Params;
	Collision1Params.AddIgnoredActor(this);
	bool b1Hit = GetWorld()->LineTraceSingleByChannel(Hit1Result, StartPos, End1Pos, ECC_Visibility, Collision1Params);

	if (b1Hit)
	{
		bIsOnHand = true;
	}
	else
	{
		bIsOnHand = false;
	}

	UE_LOG(LogTemp, Warning, TEXT("OnHnad"));

	DrawDebugLine(GetWorld(), StartPos, End1Pos, FColor::Black, false, -1, 0, 1);
}

void AEO_Food::ServerCheckOnGround_Implementation()
{
	MulticastCheckOnGround();
}

void AEO_Food::MulticastCheckOnGround_Implementation()
{
	
	FVector CharacterLocation = GetActorLocation();

	FVector StartPos = CharacterLocation;
	FVector EndPos = CharacterLocation - FVector(0, 0, 40);

	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartPos, EndPos, ECC_Visibility, CollisionParams);

	if (bHit)
	{
		bIsOnGround = true;
	}
	else
	{
		bIsOnGround = false;
	}
	UE_LOG(LogTemp, Warning, TEXT("OnGround"));

	DrawDebugLine(GetWorld(), StartPos, EndPos, FColor::Green, false, -1, 0, 1);
}

void AEO_Food::FoodVisible()
{
	meshComp->SetVisibility(true);
	changeMeshComp->SetVisibility(false);
	platedMeshComp->SetVisibility(false);
}

void AEO_Food::ChangeVisible()
{
	meshComp->SetVisibility(false);
	changeMeshComp->SetVisibility(true);
	platedMeshComp->SetVisibility(false);
}

void AEO_Food::PlatedVisible()
{
	meshComp->SetVisibility(false);
	changeMeshComp->SetVisibility(false);
	platedMeshComp->SetVisibility(true);
}

void AEO_Food::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
		if (auto block = Cast<AEO_Block>(OtherActor))
		{
			UE_LOG(LogTemp, Warning, TEXT("block Overlap"));
			//if (block->bOnItem == false)
			//{
			//block->ServerOnItem(this);
			
			//}
			if (block->bOnItem == true)
			{
				return;
			}
			if (block->bOnItem == false)
			{
				if (!bIsOnGround)
				{
					if (!bIsOnHand) {
						ServerOverlapItemOnBlock(block->sceneComp);
						//block->ServerOnItem(this);
						//boxComp->SetSimulatePhysics(false);
						block->bOnItem = true;

					}
				}
			}
		}

}

void AEO_Food::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AEO_Food, bIsOnGround);
	DOREPLIFETIME(AEO_Food, bIsOnHand);
}