// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VeryInterestingActor.generated.h"

UCLASS()
class ARSENALAPPLEPICKER_API AVeryInterestingActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AVeryInterestingActor();

	UPROPERTY(EditAnywhere, Category = "Attributes")
	USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* ConeMeshComp; // may or may not need "class". This is a foward declaration.

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* PyramidMeshComp;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* TargetMeshComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
