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

	// 获取和设置得分
	int32 GetScore() const { return Score; }
	void SetScore(int32 NewScore) { Score = NewScore; }

	// 计时器
	FTimerHandle TimerHandle;
	// 当前游戏时间
	float TimeRemaining;

	// 更新剩余时间
	void UpdateTime();

	// 当时间到达 0 时结束游戏
	void EndGame();


protected:

	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	// 玩家得分
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Score")
	int32 Score = 0;


	// Begin Actor interface
protected:

	virtual void BeginPlay() override;

	// End Actor interface
};
