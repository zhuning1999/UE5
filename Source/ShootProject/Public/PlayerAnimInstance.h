// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

class AMyCharacter;
class UCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class SHOOTPROJECT_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;//相当于beginplay
	virtual void NativeUpdateAnimation(float DeltaTime) override;//相当于tick
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AMyCharacter> PlayerCharacter;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UCharacterMovementComponent> PlayerCharacterMovement;
	UPROPERTY(BlueprintReadOnly)
	float Speed;
};
