// Fill out your copyright notice in the Description page of Project Settings.


#include "Dumm.h"

UDumm::UDumm() // constructor
{
	Health = 100;
}

void UDumm::Hello()
{
	UE_LOG(LogTemp, Warning, TEXT("Hello!"));
}
