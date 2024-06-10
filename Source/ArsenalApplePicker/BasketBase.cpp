// Fill out your copyright notice in the Description page of Project Settings.


#include "BasketBase.h"
#include "Components/PrimitiveComponent.h"
#include "AppleBase.h"
#include "ArsenalApplePickerGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"


// Sets default values
ABasketBase::ABasketBase()
	:BasketSpeed(700.0f), PaddleOffset(0.0, 0.0, 150.0), CurrentVelocity(0.0)
	, CurrentGameMode(nullptr), Controller(nullptr)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	TArray<UStaticMeshComponent*> Paddle;

	Paddle1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle1"));
	Paddle2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle2"));
	Paddle3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle3"));

	RootComponent = Root;

	
	Paddle1->SetupAttachment(RootComponent);
	Paddle2->SetupAttachment(Paddle1);
	Paddle3->SetupAttachment(Paddle2);

	PaddleArray.Push(Paddle1);
	PaddleArray.Push(Paddle2);
	PaddleArray.Push(Paddle3);

	Paddle1->SetNotifyRigidBodyCollision(true);
	Paddle2->SetNotifyRigidBodyCollision(true);
	Paddle3->SetNotifyRigidBodyCollision(true);

	//Setting Auto Possess player (pawn) to Player 0 as default.
	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

void ABasketBase::HandlePaddleDestruction()
{
	if (!PaddleArray.IsEmpty())
	{
		UStaticMeshComponent* PoppedElement = PaddleArray.Pop(true);
		
		if (PoppedElement)
		{
			FVector PaddleLocation = PoppedElement->GetComponentLocation();

			PoppedElement->DestroyComponent();
			if (PaddleLostParticles != nullptr && PaddleLostParticles->IsValid())
			{
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(this
					, PaddleLostParticles
					, PaddleLocation);
			}
		}
	}
}

APlayerController* ABasketBase::GetBasketPlayerController() const
{
	return Controller;
}

// Called when the game starts or when spawned
void ABasketBase::BeginPlay()
{
	Super::BeginPlay();

	Paddle1->OnComponentHit.AddDynamic(this, &ABasketBase::OnHit);
	Paddle2->OnComponentHit.AddDynamic(this, &ABasketBase::OnHit);
	Paddle3->OnComponentHit.AddDynamic(this, &ABasketBase::OnHit);

	CurrentGameMode = Cast<AArsenalApplePickerGameModeBase>(UGameplayStatics::GetGameMode(this));

	Controller = Cast<APlayerController>(GetController());
	
}

void ABasketBase::PreRegisterAllComponents()
{
	Super::PreRegisterAllComponents();

	Paddle2->SetRelativeLocation(PaddleOffset);
	Paddle3->SetRelativeLocation(PaddleOffset);
}

void ABasketBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalPulse, const FHitResult& Hit)
{
	AAppleBase* AppleToCatch = Cast<AAppleBase>(OtherActor);

	if (AppleToCatch)
	{
		if (CurrentGameMode != nullptr)
		{
			CurrentGameMode->HandleAppleCaught();
		}
		OtherActor->Destroy();
	}
}

// Called every frame
void ABasketBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (InputEnabled())
	{
		if (!CurrentVelocity.IsZero())
		{

			FVector NewLocation = GetActorLocation() + CurrentVelocity * DeltaTime;
			SetActorLocation(NewLocation);
		}
	}
}

// Called to bind functionality to input
void ABasketBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveRight", this, &ABasketBase::MoveRight);

}

void ABasketBase::MoveRight(float AxisValue)
{
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * BasketSpeed;

	
	//(LogTemp, Warning, TEXT("Velocity: %s"), *CurrentVelocity.ToString());
}

