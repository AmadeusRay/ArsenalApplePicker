// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AppleTreeElementBase.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AppleBase.generated.h"

UCLASS()
class ARSENALAPPLEPICKER_API AAppleBase : public AAppleTreeElementBase
	
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAppleBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Destroyed() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* AppleMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particles Effects")
	class UNiagaraSystem* AppleDestroyedParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float FloorBoundary;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	class AArsenalApplePickerGameModeBase* CurrentGameMode;

};
