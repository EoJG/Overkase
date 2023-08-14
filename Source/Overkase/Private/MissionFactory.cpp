// Fill out your copyright notice in the Description page of Project Settings.


#include "MissionFactory.h"
#include "EO_Food.h"
#include <Engine/World.h>
#include "EO_CucumberSushi.h"
#include "EO_OctopusSushi.h"
#include "Kismet/KismetMathLibrary.h"
#include "O2_sushi.h"
#include "Mooner_sushi.h"

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
        
        GetWorld()->SpawnActor<AO2_sushi>(sushiMenu2, GetActorLocation(), FRotator());
        //GetWorld()->SpawnActor<AEO_OctopusSushi>(sushiMenu3, GetActorLocation(), FRotator());

        // ����ð��� �ʱ�ȭ
        currentTime = 0;

        // �����ð��� �����ϰ� �ٽ� ��������
        createTime = FMath::RandRange(minTime, maxTime);
    }

}



void AMissionFactory::Get_MissionMenu()
{
    UWorld* World = GetWorld();
    FActorSpawnParameters param;
    param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    AO2_sushi* oeSushi = World->SpawnActor<AO2_sushi>(sushiMenu2, GetActorLocation(), FRotator(), param);
    AMooner_sushi* octorSushi = World->SpawnActor<AMooner_sushi>(sushiMenu3, GetActorLocation(), FRotator(), param);
}


