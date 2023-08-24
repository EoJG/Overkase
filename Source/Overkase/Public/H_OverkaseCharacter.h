// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "H_OverkaseCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FInputBindingDelegete, class UInputComponent*);


UCLASS()
class OVERKASE_API AH_OverkaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AH_OverkaseCharacter();

	UFUNCTION(NetMulticast, Reliable)
	void SendMulticast(int32 random);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* handR;
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* handL;


	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* crocodileMesh;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* headComp;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* hatComp;
	UPROPERTY(EditAnywhere)
	class USphereComponent* interationDistance;
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* interactionPosition;

	// delegate
	FInputBindingDelegete onInputBindingDelegate;

	// Move Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UOverkasePlayerBase* overPlayerMove;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UOverkasePlayerBase* overPlayerInteraction;

	//Enhanced Input resources
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* imc;
	UPROPERTY(EditDefaultsOnly, Category = Effect )
	class UParticleSystem* effect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "dashFX")
    class UNiagaraSystem* dashEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "dashFX")
	class UNiagaraComponent* NiagaraComponent;
	 UPROPERTY(EditAnywhere, Category = "dashFX")
    bool bShouldUseNiagara = false;

   UPROPERTY(EditDefaultsOnly, Category = Sound)
	class USoundBase* dashSound;
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	class USoundBase* pickUpSound;
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	class USoundBase* putDownSound;
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	class USoundBase* throwSound;
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	class USoundBase* chopSound;
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	class USoundBase* catchSound;
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	class USoundBase* BGMSound;
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	class USoundBase* endingSound;
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	class USoundBase* timeOutSound;
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	class UAudioComponent* BGMAudio;

	UPROPERTY(VisibleAnywhere, Category = "EO")
	TSubclassOf<class UEO_InGameInterface> inGameUIClass;
	UPROPERTY(VisibleAnywhere, Category = "EO")
	class UEO_InGameInterface* inGameUI;

	UFUNCTION(NetMulticast, Reliable)
	void MulticastOnParticle();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastOnVFX();

	UFUNCTION(Server, Reliable)
	void ServerEndVFX();
	UFUNCTION(NetMulticast, Reliable)
	void MulticastEndVFX();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastOnDashSound();
	UFUNCTION(NetMulticast, Reliable)
	void MulticastOnPickUpSound();
	UFUNCTION(NetMulticast, Reliable)
	void MulticastOnPutDownSound();
	UFUNCTION(NetMulticast, Reliable)
	void MulticastOnThrowSound();
	UFUNCTION(NetMulticast, Reliable)
	void MulticastOnChopSound();
	UFUNCTION(Server, Reliable)
	void ServerOnCatchSound();
	UFUNCTION(NetMulticast, Reliable)
	void MulticastOnCatchSound();
	
	
	UFUNCTION(NetMulticast, Reliable)
	void MulticastAddScore(int score);

	UPROPERTY(Replicated)
	float currentTime = 0;
	UPROPERTY(Replicated)
	float travelTime = 0;
	
	UFUNCTION(NetMulticast, Reliable)
	void MulticastTestFunc(FName foodTag);

	void TimeOutSound();
	void EndingSound();
	bool bEndingplay = false;
	bool bSoundPlay = false;
	bool bTimeOutPlay = false;

	//EO
	UPROPERTY()
	class AEO_Camera* eoCam;
	UPROPERTY()
	class AActor* mainCam;
	UFUNCTION(Server, Reliable)
	void ServerAddScore();
};
