// Fill out your copyright notice in the Description page of Project Settings.


#include "Chair.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AChair::AChair()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ChairComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Chair"));
	RootComponent = ChairComponent;

	ChairComponent->SetSimulatePhysics(true);

	ImpulseVelocity = 100000.0f;

	ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/StarterContent/Props/SM_Chair.SM_Chair'"));

	if (MeshAsset.Object != nullptr) // or MeshAsset.Succeeded();
	{
		ChairComponent->SetStaticMesh(MeshAsset.Object);
	}
}

// Called when the game starts or when spawned
void AChair::BeginPlay()
{
	Super::BeginPlay();

	ChairComponent->AddImpulse(FVector(0.0f, 0.0f, ImpulseVelocity));

	//SetLifeSpan(10.0f);

}

// Called every frame
void AChair::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult Hit;

	AddActorWorldOffset(FVector(1.0f, 0.0f, 0.0f), true, &Hit);
}


