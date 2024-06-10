// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AppleTreeElementBase.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TreeBase.generated.h"

class AAppleBase;

UCLASS()
class ARSENALAPPLEPICKER_API ATreeBase : public AAppleTreeElementBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATreeBase();

	void StartSpawningApples();
	void StopSpawningApples();
	void StartRedirecting();
	void StopRedirection();
	void SetShouldMove(bool bInShouldMove);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* TreeMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float MovementSpeed;

	// Left and right boundaries
	// When reached the Tree Actor moves in opposite direction

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float OuterBoundary;

	// Random Redirection only whenin inner boundary
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float InnerBoundary;

	// Chance to move in opposite direction
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
		float ChanceToRedirect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
		float RedirectTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
		float SecondsBetweenAppleDrops;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
		TSubclassOf<AAppleBase> SpawnObj;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FTimerHandle ChangeDirectionTimer;

	void ChangeDirection();

	FTimerHandle AppleSpawnTimer;

	UFUNCTION()
	void SpawnApple();

	bool bShouldMove;
};
