// Copyright Epic Games, Inc. All Rights Reserved.


#include "ShootProjectPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"

AShootProjectPlayerController::AShootProjectPlayerController()
{
	// ��ʼ��Ĭ�ϵ÷ֺ�ʱ��
	Score = 0;
	TimeRemaining = 10.0f;  // ������Ϸ��ʼʱ�� 60 ��
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

	// ������ʱ����ÿ�����һ��
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AShootProjectPlayerController::UpdateTime, 1.0f, true);
}

void AShootProjectPlayerController::UpdateTime()
{
	// ����ʣ��ʱ��
	TimeRemaining -= 1.0f;

	// ���ʱ���þ���������Ϸ
	if (TimeRemaining <= 0)
	{
		EndGame();
	}
}

void AShootProjectPlayerController::EndGame()
{
	// ֹͣ��ʱ��
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);

	// ������յ÷ֲ�������Ϸ
	UE_LOG(LogTemp, Log, TEXT("Game Over! Final Score: %d"), Score);

	// ���������ӽ�����Ϸ���߼���������ʾ UI��ֹͣ��Ϸ��
}