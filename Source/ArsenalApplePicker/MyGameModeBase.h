// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

class AChair;
/**
 *
 */
UCLASS()
class ARSENALAPPLEPICKER_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AChair> ChairToSpawn; // used to filter options down in defaults panel. Show less. Only chair.

	void SpawnChair();

protected:
	virtual void BeginPlay() override;

private:
	AChair* SpawnedChairRef;

	FTimerHandle DestroyTimer;

	FTimerHandle SpawnTimer;

	void InvokeDestroy();
};
