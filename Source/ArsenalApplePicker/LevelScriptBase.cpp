// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelScriptBase.h"
#include "Camera/CameraActor.h"

ALevelScriptBase::ALevelScriptBase()
	:Camera(nullptr), Controller(nullptr) // setting null then it's modified at the bottom.
	//So there's no garbage data.
{

}

void ALevelScriptBase::BeginPlay()
{
	Super::BeginPlay();

	Controller = GetWorld()->GetFirstPlayerController();

	if (Controller)
	{
		Controller->SetViewTarget(Camera);
	}
}
