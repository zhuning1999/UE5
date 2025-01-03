// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShootProjectProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "ShootProjectPlayerController.h"
#include "Engine/StaticMeshActor.h"
#include "MyBoActor.h"


AShootProjectProjectile::AShootProjectProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AShootProjectProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 1.0f;
}

void AShootProjectProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		// �ı� OtherActor �Ĵ�С
		FVector CurrentScale = OtherActor->GetActorScale3D();
		FVector NewScale = CurrentScale * 0.5f;  // ��С 50%

		// �����µ�����
		OtherActor->SetActorScale3D(NewScale);

		UpdateScore(OtherActor);

		Destroy();
	}
}

void AShootProjectProjectile::UpdateScore(AActor* OtherActor)
{	
	//��ȡ���controller�����ﻹ����һ��cast������ת��
	AShootProjectPlayerController* PlayerController = Cast<AShootProjectPlayerController>(GetWorld()->GetFirstPlayerController());
	AMyBoActor* MeshActor = Cast<AMyBoActor>(OtherActor);

	if (PlayerController)
	{
		// ��ȡ��ҵĵ÷ֱ�����������ҵ÷��Ǵ洢�� PlayerController ��
		// ��Ҳ���Խ��÷ִ洢�� ACharacter ���������ʵĵط�
		int32 CurrentScore = PlayerController->GetScore();

		// ���ӵ÷֣�����ÿ�λ��е������� 10 �֣�������Ҫ�ļ� 20 �֣�
		if (MeshActor->bIsImportant) CurrentScore += 20;
		else CurrentScore += 10;
		PlayerController->SetScore(CurrentScore);
		UE_LOG(LogTemp, Log, TEXT("Total Score: %d"), CurrentScore);

	}
}
