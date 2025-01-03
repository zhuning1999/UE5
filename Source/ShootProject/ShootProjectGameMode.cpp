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

	// �����Զ���� GameState ��
	static ConstructorHelpers::FClassFinder<AGameStateBase> GameStateClassFinder(TEXT("/Script/ShootProject.MyGameStateBase"));
	GameStateClass = GameStateClassFinder.Class;


}
