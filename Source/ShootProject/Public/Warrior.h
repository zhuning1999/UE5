// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCharacter.h"
#include "Warrior.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTPROJECT_API AWarrior : public AMyCharacter
{
	GENERATED_BODY()

public:
	virtual void Attack() override;
	
};
