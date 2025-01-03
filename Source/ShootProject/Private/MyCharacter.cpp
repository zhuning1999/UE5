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

	//�����
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 700.f;
	CameraBoom->SetRelativeRotation(FRotator(-40.f, 0.f, 0.f));
	//������޸ĸ����
	//SetRootComponent(CameraBoom);
	//������ŵ������
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>("Player_Camera");
	PlayerCamera->SetupAttachment(CameraBoom);
	//���ŵ�ĳһ�����
	//������ǰ�������ϣ������и���۽�Root_Socket�����λ�ÿ�������ͼ���Լ���
	//PlayerCamera->SetupAttachment(GetMesh(), FName("Root_Socket"));

	SphereComponent = CreateDefaultSubobject<USphereComponent>("Sphere Collsion");
	SphereComponent->SetSphereRadius(35.f);

	//��ɫ�����ſ�����ת��
	//������Ǹ�character�Ƿ���ſ�����ת��
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	//�����ת�������ת��
	//�����bUsePawnControlRotation�ĺ����Ƕ��������ת�����
	CameraBoom->bUsePawnControlRotation = true;
	PlayerCamera->bUsePawnControlRotation = false;

	//��ɫ�����ƶ��������ת��
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
		UEnhancedInputLocalPlayerSubsystem* SubSystem = Player->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();//��ͬ
		//UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Player);
		if (DefaultMapping) {
			SubSystem->AddMappingContext(DefaultMapping, 0);
		}
	}
	
}

void AMyCharacter::CallableFunction()
{
	//��ͼ�������֡ˢ��
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
		//���˶��ֳ������������ڼ������ǰ��X��Y����Ȼ�����λ��
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

