// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBoActor.h"

AMyBoActor::AMyBoActor()
{
	bIsImportant = FMath::RandBool();
}

void AMyBoActor::BeginPlay()
{
	Super::BeginPlay();
	bIsImportant = FMath::RandBool();
}
