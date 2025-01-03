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

		// 改变 OtherActor 的大小
		FVector CurrentScale = OtherActor->GetActorScale3D();
		FVector NewScale = CurrentScale * 0.5f;  // 缩小 50%

		// 设置新的缩放
		OtherActor->SetActorScale3D(NewScale);

		UpdateScore(OtherActor);

		Destroy();
	}
}

void AShootProjectProjectile::UpdateScore(AActor* OtherActor)
{	
	//获取玩家controller，这里还用了一个cast的类型转化
	AShootProjectPlayerController* PlayerController = Cast<AShootProjectPlayerController>(GetWorld()->GetFirstPlayerController());
	AMyBoActor* MeshActor = Cast<AMyBoActor>(OtherActor);

	if (PlayerController)
	{
		// 获取玩家的得分变量，假设玩家得分是存储在 PlayerController 中
		// 你也可以将得分存储在 ACharacter 或其他合适的地方
		int32 CurrentScore = PlayerController->GetScore();

		// 增加得分（假设每次击中敌人增加 10 分，打中重要的加 20 分）
		if (MeshActor->bIsImportant) CurrentScore += 20;
		else CurrentScore += 10;
		PlayerController->SetScore(CurrentScore);
		UE_LOG(LogTemp, Log, TEXT("Total Score: %d"), CurrentScore);

	}
}
