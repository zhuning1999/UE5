// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MyBoActor.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTPROJECT_API AMyBoActor : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "MyGo")
	bool bIsImportant = true;
	AMyBoActor();

	void BeginPlay();
};
