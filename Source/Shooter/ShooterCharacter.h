// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

UCLASS()
class SHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 앞/뒤 이동 함수
	void MoveForward(float value);

	// 좌/우 이동 함수
	void MoveRight(float value);

	// input(rate)에 따라 좌/우 회전 함수
	// rate는 normalized
	void TurnAtRate(float rate);

	// input(rate)에 따라 위/아래 회전 함수
	// rate는 normalized
	void LoopUpAtRate(float rate);

	// FireButton이 눌렸을 때 호출
	void FireWeapon();

	
	bool GetBeamEndLocation(const FVector& MuzzleSocketLocation, FVector& OutBeamLocation);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	// 캐릭터 뒤에 Camera boom (Camera) 위치
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	// 캐릭터 카메라
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	// 좌/우 회전율 (deg/sec)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float BaseTurnRate;

	// 위/아래 회전율 (deg/sec)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float BaseLookUpRate;

	// 총소리 (랜덤)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	class USoundCue* FireSound;

	// 총구
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	class UParticleSystem* MuzzleFlash;

	// 무기 사용 몽타주
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* HipFireMontage;

	// 불빛
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	class UParticleSystem* ImpactParticles;

	// 연기
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	class UParticleSystem* BeamParticles;

public:
	// CameraBoom 반환
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	// 카메라 반환
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
