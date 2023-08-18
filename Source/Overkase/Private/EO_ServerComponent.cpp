// Fill out your copyright notice in the Description page of Project Settings.


#include "EO_ServerComponent.h"
#include "Net/UnrealNetwork.h"
#include "H_OverkaseCharacter.h"
#include "EO_InGameInterface.h"

// Sets default values for this component's properties
UEO_ServerComponent::UEO_ServerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UEO_ServerComponent::BeginPlay()
{
	Super::BeginPlay();

	me = Cast<AH_OverkaseCharacter>(GetOwner());
	if (me->HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *me->GetName());
	}
}


// Called every frame
void UEO_ServerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

