// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "TestLevelScriptActor.generated.h"



/**
 *
 */
UCLASS()
class ARSENALAPPLEPICKER_API ATestLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()
public:
	ATestLevelScriptActor();



protected:
	virtual void BeginPlay() override;


};
