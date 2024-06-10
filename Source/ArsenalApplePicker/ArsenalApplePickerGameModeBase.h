// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ArsenalApplePickerGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ARSENALAPPLEPICKER_API AArsenalApplePickerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	void HandleAppleCaught();
	void HandleAppleLost();

	UFUNCTION(BlueprintCallable)
	float GetGameStartDelay() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void HandleGameOver(bool bWonGame);

	UPROPERTY(EditAnywhere, Category = "Setup")
	int32 ApplesToCatch{ 10 };

	UPROPERTY(EditAnywhere, Category = "Setup")
	int32 ApplesToLose{ 3 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float GameStartDelay{ 5.0f };

	// To specifiy widget blueprint / type in Editor
	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<class UUserWidget> GameWidgetType;

	UPROPERTY()
		class UApplePickerWidgetBase* Widget;

private:
	int32 ApplesCaught{ 0 };
	int32 ApplesLost{ 0 };

	class ABasketBase* Basket{ nullptr };

	void HandleGameStart();

	void UpdateWidgetText();
	
};
