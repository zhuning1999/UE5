// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMeshActor.h"
#include "MyGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTPROJECT_API AMyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:   

    // ���ɾ�̬����ĺ���
    void BeginPlay();
};
