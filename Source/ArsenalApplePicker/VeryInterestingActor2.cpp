// Fill out your copyright notice in the Description page of Project Settings.


#include "VeryInterestingActor2.h"

// Sets default values
AVeryInterestingActor2::AVeryInterestingActor2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("UScene Root Component"));
	Mesh = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));

	//RootComponent = Root;
	// Or...
	SetRootComponent(Root); // does additional checks


	Mesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AVeryInterestingActor2::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVeryInterestingActor2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

