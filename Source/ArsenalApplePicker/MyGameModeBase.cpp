//// Fill out your copyright notice in the Description page of Project Settings.
//
//
//#include "MyGameModeBase.h"
//#include "Chair.h"
//
//void AMyGameModeBase::BeginPlay()
//{
//	Super::BeginPlay();
//
//	//FTransform SpawnLocation; //Calling FTransform and calling it SpawnLocation.
//	dest
//							  
//	//My way						  
//	//SpawnLocation.SetRotation(FQuat(2));
//	//SpawnLocation.SetLocation(FVector(0.0f, 0.0f, 100.0f));
//	//SpawnLocation.SetScale3D(FVector(4));
//
//	//UE_LOG(LogTemp, Warning, TEXT("Rotation: %s "), *SpawnLocation.ToString());
//
//	//Lesson's way
//	/*FTransform SpawnLocation{ FRotator(0.0f, 90.0f, 0.0f), FVector(100.0f), FVector(1.0f) };
//	UE_LOG(LogTemp, Warning, TEXT("Transform (p, r, s): %s"), *SpawnLocation.ToString());*/
//
//	FTransform SpawnLocation;
//	SpawnLocation.SetLocation(FVector(0.0f, 0.0f, 100.0f));
//
//
//	UWorld* MyWorld = GetWorld();
//	if (MyWorld != nullptr)
//	{
//		SpawnedChairRef = MyWorld->SpawnActor<AChair>(ChairToSpawn, SpawnLocation);
//
//		MyWorld->GetTimerManager().SetTimer(DestroyTimer, this, &AMyGameModeBase::InvokeDestroy, 5.0f);
//	
//	}
//}
//
//void AMyGameModeBase::InvokeDestroy()
//{
//	SpawnedChairRef->Destroy();
//}


// exercise

// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "Chair.h"

void AMyGameModeBase::SpawnChair()
{
	FTransform SpawnLocation;
	SpawnLocation.SetLocation(FVector(0.0f, 0.0f, 100.0f));

	UWorld* MyWorld = GetWorld();
	if (MyWorld)
	{
		SpawnedChairRef = MyWorld->SpawnActor<AChair>(ChairToSpawn, SpawnLocation);

		MyWorld->GetTimerManager().SetTimer(DestroyTimer, this, &AMyGameModeBase::InvokeDestroy, 5.0f);

	}

}

void AMyGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(SpawnTimer, this, &AMyGameModeBase::SpawnChair, 2.0f);

}

void AMyGameModeBase::InvokeDestroy()
{
	SpawnedChairRef->Destroy();
}
