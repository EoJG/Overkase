// Fill out your copyright notice in the Description page of Project Settings.


#include "MissionFactory.h"
#include "EO_Food.h"
#include <Engine/World.h>
#include "EO_CucumberSushi.h"
#include "EO_OctopusSushi.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AMissionFactory::AMissionFactory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMissionFactory::BeginPlay()
{
	Super::BeginPlay();
	
    createTime = FMath::RandRange(minTime, maxTime);

}

// Called every frame
void AMissionFactory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    currentTime += DeltaTime;
    if (currentTime > createTime)
    {
        
        GetWorld()->SpawnActor<AEO_CucumberSushi>(sushiMenu2, GetActorLocation(), FRotator());
        //GetWorld()->SpawnActor<AEO_OctopusSushi>(sushiMenu3, GetActorLocation(), FRotator());

        // 경과시간을 초기화
        currentTime = 0;

        // 생성시간을 랜덤하게 다시 설정하자
        createTime = FMath::RandRange(minTime, maxTime);
    }

}



void AMissionFactory::Get_MissionMenu()
{
    UWorld* World = GetWorld();
    FActorSpawnParameters param;
    param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    AEO_CucumberSushi* oeSushi = World->SpawnActor<AEO_CucumberSushi>(sushiMenu2, GetActorLocation(), FRotator(), param);
    AEO_OctopusSushi* octorSushi = World->SpawnActor<AEO_OctopusSushi>(sushiMenu3, GetActorLocation(), FRotator(), param);
}


