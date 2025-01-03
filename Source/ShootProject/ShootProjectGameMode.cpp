// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShootProjectGameMode.h"
#include "ShootProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AShootProjectGameMode::AShootProjectGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// 设置自定义的 GameState 类
	static ConstructorHelpers::FClassFinder<AGameStateBase> GameStateClassFinder(TEXT("/Script/ShootProject.MyGameStateBase"));
	GameStateClass = GameStateClassFinder.Class;


}
