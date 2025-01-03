// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPPPlayerController.generated.h"

/**
 * 虚幻运行顺序：
 * AMyCharacter构造函数 -> Onpossess() ->beginplay()
 * 
 * HUD
 */
UCLASS()
class SHOOTPROJECT_API ACPPPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void OnPossess(APawn* InPawn) override;

};
