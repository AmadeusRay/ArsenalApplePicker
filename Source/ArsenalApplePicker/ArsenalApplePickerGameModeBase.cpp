// Copyright Epic Games, Inc. All Rights Reserved.


#include "ArsenalApplePickerGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "BasketBase.h"
#include "AppleBase.h"
#include "treebase.h"
//#include "AppleTreeElementBase.h" no need to include since it's in inherited.

#include "ApplePickerWidgetBase.h"

void AArsenalApplePickerGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (GameWidgetType)
		if (GameWidgetType)
		{
			Widget = Cast<UApplePickerWidgetBase>(CreateWidget(GetWorld(), GameWidgetType));

			if (Widget)
			{
				Widget->AddToViewport();
				UpdateWidgetText();
			}
		}

	Basket = Cast<ABasketBase>(UGameplayStatics::GetPlayerPawn(this, 0));

	if (Basket)
	{
		Basket->DisableInput(nullptr);
	}

	FTimerHandle GameStartCountdownTimer;

	GetWorld()->GetTimerManager().SetTimer(GameStartCountdownTimer, 
		this, 
		&AArsenalApplePickerGameModeBase::HandleGameStart,
		GameStartDelay,
		false);
}

void AArsenalApplePickerGameModeBase::HandleAppleCaught()
{
	ApplesCaught = ApplesCaught + 1;
	UpdateWidgetText();

	UE_LOG(LogTemp, Warning, TEXT("Apple Caught!"));
	UE_LOG(LogTemp, Warning, TEXT("Total Apples Caught: %d"), ApplesCaught);

	if (ApplesCaught >= ApplesToCatch)
	{
		// We win the game
		HandleGameOver(true);
	}
}

void AArsenalApplePickerGameModeBase::HandleAppleLost()
{
	ApplesLost = ApplesLost + 1;

	UE_LOG(LogTemp, Warning, TEXT("Apple Lost!"));
	UE_LOG(LogTemp, Warning, TEXT("Total Apples Lost: %d"), ApplesLost);

	if (Basket != nullptr)
	{
		Basket->HandlePaddleDestruction();
	}

	if (ApplesLost >= ApplesToLose)
	{
		// We lose the game
		HandleGameOver(false);
	}
}

float AArsenalApplePickerGameModeBase::GetGameStartDelay() const
{
	return GameStartDelay;
}

void AArsenalApplePickerGameModeBase::HandleGameOver_Implementation(bool bWonGame)
{
	TArray<AActor*> FoundAppleTreeElements;
	UGameplayStatics::GetAllActorsOfClass(GetWorld()
		, AAppleTreeElementBase::StaticClass()
		, FoundAppleTreeElements);

	for (auto Ptr : FoundAppleTreeElements)
	{
		if (ATreeBase* TempTreePtr = Cast<ATreeBase>(Ptr))
		{
			TempTreePtr->StopSpawningApples();
			TempTreePtr->StopRedirection();
			TempTreePtr->SetShouldMove(false);
		}
		else if (AAppleBase* TempApplePtr = Cast <AAppleBase>(Ptr))
		{
			// Destroy remaining apples
			TempApplePtr->Destroy();
		}
	}
	if (Basket && Basket->GetBasketPlayerController())
	{
		Basket->DisableInput(Basket->GetBasketPlayerController());
		Basket->SetActorTickEnabled(false);
		//Basket->SetActorHiddenInGame(true;
	}

	if (Widget)
	{
		Widget->SetGameOverText(bWonGame);
	}
}

void AArsenalApplePickerGameModeBase::HandleGameStart()
{
	TArray<AActor*> FoundAppleTreeElements;
	UGameplayStatics::GetAllActorsOfClass(GetWorld()
		, AAppleTreeElementBase::StaticClass()
		, FoundAppleTreeElements);

	for (auto Ptr : FoundAppleTreeElements)
	{
		if (ATreeBase* TempTreePtr = Cast<ATreeBase>(Ptr))
		{
			TempTreePtr->StartSpawningApples();
			TempTreePtr->StartRedirecting();
			TempTreePtr->SetShouldMove(true);
		}
	}
	if (Basket && Basket->GetBasketPlayerController())
	{
		Basket->EnableInput(Basket->GetBasketPlayerController());
		Basket->SetActorTickEnabled(true);
	}
}

void AArsenalApplePickerGameModeBase::UpdateWidgetText()
{
	if (Widget)
	{
		Widget->SetAppleCollectedText(ApplesCaught, ApplesToCatch);
	}
}
