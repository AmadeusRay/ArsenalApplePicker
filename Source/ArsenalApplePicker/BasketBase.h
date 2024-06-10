// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasketBase.generated.h"

UCLASS()
class ARSENALAPPLEPICKER_API ABasketBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasketBase();

	void HandlePaddleDestruction();

	APlayerController* GetBasketPlayerController() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PreRegisterAllComponents() override;

	UPROPERTY(EditAnywhere, BlueprintReadWRite, Category = "Setup")
		float BasketSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWRite, Category = "Setup")
		FVector PaddleOffset;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* Paddle1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* Paddle2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* Paddle3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particles Effects")
		class UNiagaraSystem* PaddleLostParticles;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalPulse, const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	FVector CurrentVelocity;

	class AArsenalApplePickerGameModeBase* CurrentGameMode;

	void MoveRight(float AxisValue);

	TArray<UStaticMeshComponent*> PaddleArray;

	APlayerController* Controller;
};
