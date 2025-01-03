// Copyright Epic Games, Inc. All Rights Reserved.


#include "ShootProjectPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"

AShootProjectPlayerController::AShootProjectPlayerController()
{
	// 初始化默认得分和时间
	Score = 0;
	TimeRemaining = 10.0f;  // 例如游戏开始时有 60 秒
}

void AShootProjectPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// get the enhanced input subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}

	// 启动计时器，每秒更新一次
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AShootProjectPlayerController::UpdateTime, 1.0f, true);
}

void AShootProjectPlayerController::UpdateTime()
{
	// 减少剩余时间
	TimeRemaining -= 1.0f;

	// 如果时间用尽，结束游戏
	if (TimeRemaining <= 0)
	{
		EndGame();
	}
}

void AShootProjectPlayerController::EndGame()
{
	// 停止计时器
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);

	// 输出最终得分并结束游戏
	UE_LOG(LogTemp, Log, TEXT("Game Over! Final Score: %d"), Score);

	// 这里可以添加结束游戏的逻辑，例如显示 UI、停止游戏等
}