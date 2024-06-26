// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Chair.generated.h"

UCLASS()
class ARSENALAPPLEPICKER_API AChair : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChair();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* ChairComponent;

	UPROPERTY(EditAnywhere)
	float ImpulseVelocity;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
