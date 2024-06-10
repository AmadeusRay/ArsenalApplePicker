// Fill out your copyright notice in the Description page of Project Settings.


#include "AppleBase.h"
#include "ArsenalApplePickerGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
AAppleBase::AAppleBase()
	:FloorBoundary(-680.0f), CurrentGameMode(nullptr)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AppleMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AppleMeshComponent"));

	RootComponent = AppleMeshComponent;

	AppleMeshComponent->SetSimulatePhysics(true);

}

// Called when the game starts or when spawned
void AAppleBase::BeginPlay()
{
	Super::BeginPlay();

	CurrentGameMode = Cast<AArsenalApplePickerGameModeBase>(UGameplayStatics::GetGameMode(this));
	
}

void AAppleBase::Destroyed()
{
	Super::Destroyed();

	if (AppleDestroyedParticles != nullptr && AppleDestroyedParticles->IsValid())
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this
			, AppleDestroyedParticles
			, GetActorLocation());
	}
}

// Called every frame
void AAppleBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetActorLocation().Z <= FloorBoundary)
	{
		if (CurrentGameMode != nullptr)
		{
			CurrentGameMode->HandleAppleLost();
		}

		Destroy();
	}
}

