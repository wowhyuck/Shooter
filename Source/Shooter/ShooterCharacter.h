﻿// Fill out your copyright notice in the Description page of Project Settings.

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

	// 마우스 X 이동 값에 따라 컨트롤러 회전하기
	// value는 마우스 이동값
	void Turn(float value);

	// 마우스 Y 이동 값에 따라 컨트롤러 회전하기
	// value는 마우스 이동값
	void LookUp(float value);


	// FireButton이 눌렸을 때 호출
	void FireWeapon();

	bool GetBeamEndLocation(const FVector& MuzzleSocketLocation, FVector& OutBeamLocation);

	// 줌인 버튼에 따라 (bAiming이 true 또는 false) 함수 호출
	void AimingButtonPressed();
	void AimingButtonReleased();

	void CameraInterpZoom(float DeltaTime);

	// 조준 여부에 따라 회전율 세팅
	void SetLookRates();

	
	void CalculateCrosshairSpread(float DeltaTime);

	void StartCrosshairBulletFire();

	UFUNCTION()
	void FinishCrosshairBulletFire();

	void FireButtonPressed();
	void FireButtonReleased();

	void StartFireTimer();

	UFUNCTION()
	void AutoFireReset();

	// Crosshair에 포착된 아이템 (Line Trace)
	bool TraceUnderCrosshairs(FHitResult& OutHitResult, FVector& OutHitLocation);

	// OverlappedItemCount > 0 일 때, 아이템 trace하기
	void TraceForItems();

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

	// 기본 좌/우 회전율 (deg/sec)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float BaseTurnRate;

	// 기본 위/아래 회전율 (deg/sec)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float BaseLookUpRate;

	// 조준 안 할 때 좌/우 회전율 (deg/sec)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float HipTurnRate;

	// 조준 안 할 때 위/아래 회전율 (deg/sec)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float HipLookUpRate;

	// 조준(zoom-in)할 때 좌/우 회전율 (deg/sec)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float AimingTurnRate;

	// 조준(zoom-in)할 때 위/아래 회전율 (deg/sec)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float AimingLookUpRate;

	// 조준 안 할 때 마우스 감도에 따른 scale factor
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"), meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float MouseHipTurnRate;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"), meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float MouseHipLookUpRate;

	// 조준 할 때 마우스 감도에 따른 scale factor
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"), meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float MouseAimingTurnRate;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"), meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float MouseAimingLookUpRate;

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

	// 줌인 여부
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
	bool bAiming;

	// 카메라 기본 field of value(시야) 값
	float CameraDefaultFOV;

	// 카메라 줌인 field of value 값
	float CameraZoomedFOV;

	// 현재 프레임 카메라 field of value 값
	float CameraCurrentFOV;

	// 줌인 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	float ZoomInterpSpeed;

	// Crosshair Spread 종합 factor 결정하기
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Crosshairs, meta = (AllowPrivateAccess = "true"))
	float CrosshairSpreadMultiplier;

	// 움직일 때 factor (Crosshair Spread) 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Crosshairs, meta = (AllowPrivateAccess = "true"))
	float CrosshairVelocityFactor;

	// 캐릭터가 공중에 있을 때 factor (Crosshair Spread)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Crosshairs, meta = (AllowPrivateAccess = "true"))
	float CrosshairInAirFactor;

	// 조준할 때 factor (Crosshair Spread)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Crosshairs, meta = (AllowPrivateAccess = "true"))
	float CrosshairAimFactor;

	// 사격했을 때 factor (Crosshair Spread)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Crosshairs, meta = (AllowPrivateAccess = "true"))
	float CrosshairShootingFactor;

	// 발사했을 때 변수
	float ShootTimeDuration;
	bool bFiringBullet;
	FTimerHandle CrosshairShootTimer;

	// 마우스 왼쪽 버튼 눌렸는지 여부
	bool bFireButtonPressed;

	// 발사할 수 있을 때 true, 타이머동안 기다릴 때 false
	bool bShouldFire;

	// 연사 수치
	float AutomaticFireRate;

	// 발사 간의 타이머 세팅
	FTimerHandle AutoFireTimer;

	// 매 프레임마다 아이템을 trace해야한다면 true
	bool bShouldTraceForItems;

	// 오버랩된 아이템 수
	int8 OverlappedItemCount;

public:
	// CameraBoom 반환
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	// 카메라 반환
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	// 줌인 여부 반환
	FORCEINLINE bool GetAiming() const { return bAiming; }

	UFUNCTION(BlueprintCallable)
	float GetCrosshairSpreadMultiplier() const;

	FORCEINLINE int8 GetOverlappedItemCount() const{ return OverlappedItemCount; }

	// OverlappedItemCount 더하기/빼기, bShouldTraceForItems 업데이트하기
	void IncrementOverlappedItemCount(int8 Amount);
};
