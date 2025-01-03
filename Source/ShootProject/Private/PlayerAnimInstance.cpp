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
		//���ص�UCharacterMovementComponent�������ɫ���˶��߼��������ߡ��ܲ�����Ծ����Ӿ�ȣ���ͨ�������������Կ��ƽ�ɫ�������˶�����������ײ����Ϊ��
		PlayerCharacterMovement = PlayerCharacter->GetCharacterMovement();
	}
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
	if (PlayerCharacterMovement) {
		//��PlayerCharacterMovement���ص��ٶ�ת��ΪXYƽ���ϵ��ٶȱ���
		//������ô�࣬��ʵ����Ϊ��ÿ�����ٶ�
		Speed = UKismetMathLibrary::VSizeXY(PlayerCharacterMovement->Velocity);
	}
}
