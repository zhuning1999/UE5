// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	PlayerCharacter = Cast<AMyCharacter>(TryGetPawnOwner());
	if (PlayerCharacter) {
		//返回的UCharacterMovementComponent负责处理角色的运动逻辑（如行走、跑步、跳跃、游泳等）。通过这个组件，可以控制角色的物理运动、重力、碰撞等行为。
		PlayerCharacterMovement = PlayerCharacter->GetCharacterMovement();
	}
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
	if (PlayerCharacterMovement) {
		//将PlayerCharacterMovement返回的速度转化为XY平面上的速度标量
		//干了这么多，其实就是为了每秒获得速度
		Speed = UKismetMathLibrary::VSizeXY(PlayerCharacterMovement->Velocity);
	}
}
