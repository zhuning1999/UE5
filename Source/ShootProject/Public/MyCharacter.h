// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;


class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

class USphereComponent;

UCLASS()
class SHOOTPROJECT_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

	UFUNCTION(BlueprintCallable, Category = "Action")
	virtual void Attack();
	float WarriorAttack = 101.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//func learning
	UFUNCTION(BlueprintCallable)
	void CallableFunction();
	UFUNCTION(BlueprintPure)
	bool PureFunction();
	UFUNCTION(BlueprintImplementableEvent)
	void MyBlueprintFunc();

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

private:
	//property learning
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "U|test", meta = (AllowPrivateAccess = "true"))
	float testlen;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> PlayerCamera;
	
	//Ìí¼ÓÔ²ÐÎÅö×²Ìå
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Sphere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> SphereComponent;

	//Input
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> DefaultMapping;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> AttackAction;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
