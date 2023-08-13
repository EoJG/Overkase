// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EO_Food.h"
#include "MissionFactory.generated.h"

UCLASS()
class OVERKASE_API AMissionFactory : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMissionFactory();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


//========================================================================================

	// 주문표 미션생성하기
public:
	UPROPERTY(EditAnywhere, Category = "menu")
	TSubclassOf<class AEO_Food> sushiMenu1;

	UPROPERTY(EditAnywhere, Category = "menu")
	TSubclassOf<class AEO_CucumberSushi> sushiMenu2;

	UPROPERTY(EditAnywhere, Category = "menu")
	TSubclassOf<class AEO_OctopusSushi> sushiMenu3;



	/*UPROPERTY(BlueprintReadWrite, Category = sushiMenu)
	class AEO_Food* cucumberSushi;
	
	UPROPERTY(BlueprintReadWrite, Category = sushiMenu)
	class AEO_Food* octorSushi;

	UPROPERTY(BlueprintReadWrite, Category = sushiMenu)
	class AEO_Food* Hamburger;*/

	UPROPERTY(BlueprintReadWrite, Category = Timer)
	float Getmisiiontime = 0;

	UPROPERTY(BlueprintReadWrite, Category = Timer)
	float Extinctiontime = 60;

	UPROPERTY(BlueprintReadWrite, Category = Timer)
    float createTime = 2 ; //생성시간, 시간이니까 float

    UPROPERTY(BlueprintReadWrite, Category = Timer)
    float currentTime = 0 ; 


	UPROPERTY(BlueprintReadWrite, Category = Timer)
    float minTime = 1;

    UPROPERTY(BlueprintReadWrite, Category = Timer)
    float maxTime = 5;



	void Get_MissionMenu();

};
