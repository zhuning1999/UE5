// Fill out your copyright notice in the Description page of Project Settings.


#include "Warrior.h"
#include "GameFramework/SpringArmComponent.h"


void AWarrior::Attack()
{
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Blue, FString::Printf(TEXT("Warrior %f is ready!"), WarriorAttack));
}
