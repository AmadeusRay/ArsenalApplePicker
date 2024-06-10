// Fill out your copyright notice in the Description page of Project Settings.


#include "TreeBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "AppleBase.h"

// Sets default values
ATreeBase::ATreeBase()
	:MovementSpeed(550.0f), OuterBoundary(900.0f), InnerBoundary(600.0f), 
	ChanceToRedirect(0.4f), RedirectTime(1.0f), 
	SecondsBetweenAppleDrops(1.0f), bShouldMove(false)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TreeMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TreeMeshComponent"));

	RootComponent = TreeMeshComponent;
}

// Called when the game starts or when spawned
void ATreeBase::BeginPlay()
{
	Super::BeginPlay();
}

void ATreeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bShouldMove)
	{
		FVector TempLocation{ GetActorLocation() };

		// Check is Apple Tree within bounds
		if (TempLocation.Y <= -OuterBoundary)
		{
			// Move Right
			MovementSpeed = FMath::Abs(MovementSpeed);
			SpawnApple();
		}
		else if (TempLocation.Y >= OuterBoundary)
		{
			// Move Left
			MovementSpeed = -(FMath::Abs(MovementSpeed));
			SpawnApple();
		}

		//Add offset
		//Set new location
		TempLocation.Y += MovementSpeed * DeltaTime;
		SetActorLocation(TempLocation);
	}
}

void ATreeBase::ChangeDirection()
{
	if (bShouldMove)
	{
		FVector TempPosition = GetActorLocation();


		// Only redirect if within InnerBoundary
		if (TempPosition.Y <= InnerBoundary && TempPosition.Y >= -InnerBoundary)
		{
			if (FMath::FRand() <= ChanceToRedirect)
			{

				// change direction
				MovementSpeed = MovementSpeed * -1.0f;
			}
		}
	}
}

void ATreeBase::SpawnApple()
{
	// Get TreeBase current location
	FVector SpawnLoc = GetActorLocation();
	FRotator SpawnRot = GetActorRotation();

	// Add offset randomly to the left or to the right of the current location

		if (FMath::FRand() <= 0.50f)
		{
			SpawnLoc.Y += 150.0f;
		}
		else
		{
			SpawnLoc.Y -= 150.0f;
		}

	// Spawn apple to a new offset location
	GetWorld()->SpawnActor<AAppleBase>(SpawnObj, SpawnLoc, SpawnRot);              
}

void ATreeBase::StartSpawningApples()
{
	GetWorld()->GetTimerManager().SetTimer(AppleSpawnTimer, 
		this, 
		&ATreeBase::SpawnApple, 
		SecondsBetweenAppleDrops, 
		true, 
		2.0f);
}

void ATreeBase::StartRedirecting()
{
	GetWorld()->GetTimerManager().SetTimer(ChangeDirectionTimer, 
		this, 
		&ATreeBase::ChangeDirection, 
		RedirectTime, 
		true, 
		2.5f);
}

void ATreeBase::StopSpawningApples()
{
	GetWorld()->GetTimerManager().ClearTimer(AppleSpawnTimer);
	//GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}

void ATreeBase::StopRedirection()
{
	GetWorld()->GetTimerManager().ClearTimer(ChangeDirectionTimer);
}

void ATreeBase::SetShouldMove(bool bInShouldMove)
{
	bShouldMove = bInShouldMove;
}
