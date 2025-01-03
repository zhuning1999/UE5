// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShootProjectPlayerController.generated.h"

class UInputMappingContext;

/**
 *
 */
UCLASS()
class SHOOTPROJECT_API AShootProjectPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AShootProjectPlayerController();

	// ��ȡ�����õ÷�
	int32 GetScore() const { return Score; }
	void SetScore(int32 NewScore) { Score = NewScore; }

	// ��ʱ��
	FTimerHandle TimerHandle;
	// ��ǰ��Ϸʱ��
	float TimeRemaining;

	// ����ʣ��ʱ��
	void UpdateTime();

	// ��ʱ�䵽�� 0 ʱ������Ϸ
	void EndGame();


protected:

	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	// ��ҵ÷�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Score")
	int32 Score = 0;


	// Begin Actor interface
protected:

	virtual void BeginPlay() override;

	// End Actor interface
};
