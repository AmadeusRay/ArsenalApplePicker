// Fill out your copyright notice in the Description page of Project Settings.


#include "VeryInterestingActor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AVeryInterestingActor::AVeryInterestingActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	ConeMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ConeMeshComp"));
	TargetMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TargetMeshComp"));
	PyramidMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PyramidMeshComp"));

	


	RootComponent = RootComp;
	ConeMeshComp->SetupAttachment(RootComponent);
	
	TargetMeshComp->SetupAttachment(RootComponent);

	TargetMeshComp->AddWorldOffset(FVector(0.0f, 150.0, 0.0f));

	PyramidMeshComp->SetupAttachment(TargetMeshComp);

}

// Called when the game starts or when spawned
void AVeryInterestingActor::BeginPlay()
{
	Super::BeginPlay();
	
	PyramidMeshComp->AddWorldOffset(FVector(0.0f, 0.0f, 100.0f));

	FAttachmentTransformRules MyTransformRules{ EAttachmentRule::KeepWorld, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, false };

	PyramidMeshComp->AttachToComponent(ConeMeshComp, MyTransformRules); // MyTransformRules, passing in a struct from abov. Passing in specifiers.
}
// Called every frame
void AVeryInterestingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//PyramidMeshComp->AddRelativeRotation(FRotator(0.0f, 1.0f, 0.0f));

}

