// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SphereComponent.h"


// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//相机杆
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 700.f;
	CameraBoom->SetRelativeRotation(FRotator(-40.f, 0.f, 0.f));
	//如果想修改根组件
	//SetRootComponent(CameraBoom);
	//相机附着到相机杆
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>("Player_Camera");
	PlayerCamera->SetupAttachment(CameraBoom);
	//附着到某一物件上
	//这里就是绑到人物脚上，那里有个插槽叫Root_Socket（插槽位置可以在蓝图里自己设
	//PlayerCamera->SetupAttachment(GetMesh(), FName("Root_Socket"));

	SphereComponent = CreateDefaultSubobject<USphereComponent>("Sphere Collsion");
	SphereComponent->SetSphereRadius(35.f);

	//角色不随着控制器转向
	//含义就是该character是否跟着控制器转动
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	//相机杆转向，相机不转向
	//这里的bUsePawnControlRotation的含义是对于整体的转向控制
	CameraBoom->bUsePawnControlRotation = true;
	PlayerCamera->bUsePawnControlRotation = false;

	//角色根据移动方向进行转向
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);

	UE_LOG(LogTemp, Warning, TEXT("AMyCharacter::AMyCharacter"));
}

void AMyCharacter::Attack()
{
	UE_LOG(LogTemp, Warning, TEXT("Attack from character"));
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("AMyCharacter::BeginPlay"));
	Super::BeginPlay();
	//MyBlueprintFunc();

	if (const ULocalPlayer* Player = (GEngine && GetWorld()) ? GEngine->GetFirstGamePlayer(GetWorld()) : nullptr) {
		UEnhancedInputLocalPlayerSubsystem* SubSystem = Player->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();//下同
		//UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Player);
		if (DefaultMapping) {
			SubSystem->AddMappingContext(DefaultMapping, 0);
		}
	}
	
}

void AMyCharacter::CallableFunction()
{
	//蓝图里面的逐帧刷新
	//UE_LOG(LogTemp, Warning, TEXT("Callable"));
}

bool AMyCharacter::PureFunction()
{
	return false;
}

void AMyCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MoveVector = Value.Get<FVector2D>();
	if (Controller) {
		//将运动分成两个方向，现在计算出当前对X或Y朝向，然后计算位移
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(ForwardDirection, MoveVector.X);
		AddMovementInput(RightDirection, MoveVector.Y);

	}
}

void AMyCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookVector = Value.Get<FVector2D>();
	if (Controller) {
		AddControllerPitchInput(LookVector.Y);
		AddControllerYawInput(LookVector.X);
	}
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent) {
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyCharacter::Look);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AMyCharacter::Attack);
	}
}

