// Fill out your copyright notice in the Description page of Project Settings.


#include "OverkasePlayerBase.h"

// Sets default values for this component's properties
UOverkasePlayerBase::UOverkasePlayerBase()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	bWantsInitializeComponent = true;

}


void UOverkasePlayerBase::InitializeComponent()
{
	Super::InitializeComponent();
	me = Cast<AH_OverkaseCharacter>(GetOwner());
	//UE_LOG(LogTemp,Warning,TEXT("%s"), *me->GetName());
	moveComp = me->GetCharacterMovement();
	//UE_LOG(LogTemp,Warning,TEXT("%s"), *moveComp->GetCharacterOwner()->GetName());


	//바인딩 처리
	me->onInputBindingDelegate.AddUObject(this, &UOverkasePlayerBase::SetupInputBinding);
}

// Called when the game starts
void UOverkasePlayerBase::BeginPlay()
{
	Super::BeginPlay();

	// ...

	me = Cast<AH_OverkaseCharacter>(GetOwner());

	moveComp = me->GetCharacterMovement();

	
}


// Called every frame
void UOverkasePlayerBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

