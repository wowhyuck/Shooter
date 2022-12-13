// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AmmoType.h"
#include "ShooterCharacter.generated.h"


UENUM(BlueprintType)
enum class ECombatState : uint8
{
	ECS_Unoccupied UMETA(DisplayName = "Unoccupied"),
	ECS_FireTimerInProgress UMETA(DisplayName = "FireTimerInProgress"),
	ECS_Reloading UMETA(DisplayName = "Reloading"),

	ECS_MAX UMETA(DisplayName = "DefaultMax")
};

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

	// 기본 무기 생성 및 장착하기
	class AWeapon* SpawnDefaultWeapon();

	// 무기 장착 및 캐릭터 메시에 붙이기
	void EquipWeapon(AWeapon* WeaponToEquip);

	// 무기를 떨어트려 놓기
	void DropWeapon();

	void SelectButtonPressed();
	void SelectButtonReleased();

	// 장착된 무기를 버리고 현재 조준된 아이템을 장착하기
	void SwapWeapon(AWeapon* WeaponToSwap);

	// 탄창 맵 초기화
	void InitializeAmmoMap();

	// 무기에 탄약이 있는지 확인하기
	bool WeaponHasAmmo();

	// FireWeapon에 있는 함수들
	void PlayFireSound();
	void SendBullet();
	void PlayGunfireMontage();
	
	// R키를 누를 때
	void ReloadButtonPressed();

	// 무기 장전 다루기
	void ReloadWeapon();

	// 장착한 무기의 탄약 타입을 갖고 있는지 확인하기
	bool CarryingAmmo();

	// 애니메이션 블루프린트에서 Grab Clip notify와 함께 불러오기
	UFUNCTION(BlueprintCallable)
	void GrabClip();

	// 애니메이션 블루프린트에서 Release Clip notify와 함께 불러오기
	UFUNCTION(BlueprintCallable)
	void ReleaseClip();

	void CrouchButtonPressed();

	virtual void Jump() override;

	// 앉을/일어날 때 캡슐 높이(반) interpolation
	void InterpCapsuleHalfHeight(float DeltaTime);

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	float CameraDefaultFOV;

	// 카메라 줌인 field of value 값
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
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

	// 최근 프레임에 부딪힌 AItem 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Items, meta = (AllowPrivateAccess = "true"))
	class AItem* TraceHitItemLastFrame;

	// 현재 장착중인 무기
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
	AWeapon* EquippedWeapon;

	// default weapon class를 블루프린트에서 세팅하기
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AWeapon> DefaultWeaponClass;

	// TraceForItems에 있는 플레이어가 조준한 현재 아이템 (null이 될 수 있음)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
	AItem* TraceHitItem;

	// 카메라부터 interpolation하기 위한 outward distance ( Forward * A )
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Items, meta = (AllowPrivateAccess = "true"))
	float CameraInterpDistance;

	// 카메라부터 interpolation하기 위한 upward distance ( Up * B)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Items, meta = (AllowPrivateAccess = "true"))
	float CameraInterpElevation;

	// 탄약 타입과 개수를 저장하는 맵
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Items, meta = (AllowPrivateAccess = "true"))
	TMap<EAmmoType, int32> AmmoMap;

	// 9mm 탄약 초기 개수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Items, meta = (AllowPrivateAccess = "true"))
	int32 Starting9mmAmmo;

	// AR 탄약 초기 개수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Items, meta = (AllowPrivateAccess = "true"))
	int32 StartingARAmmo;

	// 전투 상태
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
	ECombatState CombatState;

	// 장전 애니메이션 몽타주
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* ReloadMontage;
	
	UFUNCTION(BlueprintCallable)
	void FinishReloading();

	// 장전 중에 처음 탄창 잡을 때 탄창의 transform
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
	FTransform ClipTransform;

	// 장전 중에 캐릭터 손에 붙일 Scene Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
	USceneComponent* HandSceneComponent;

	// 앉을 때 true
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bCrouching;

	// 기본 이동 속도
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float BaseMovementSpeed;

	// 앉을 때 이동 속도
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float CrouchMovementSpeed;

	// 현재 캡슐 높이(반)
	float CurrentCapsuleHalfHeight;

	// 앉아 있지 않을 때 캡슐 높이(반)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float StandingCapsuleHalfHeight;

	// 앉을 때 캡슐 높이(반)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float CrouchingCapsuleHalfHeight;

	// 앉아 있지 않을 때 기본 마찰력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float BaseGroundFriction;

	// 앉아 있을 때 마찰력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float CrouchingGroundFriction;

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

	FVector GetCameraInterpLocation();

	void GetPickupItem(AItem* Item);

	FORCEINLINE ECombatState GetCombatState() const { return CombatState; }
	FORCEINLINE bool GetCrouching() const { return bCrouching; }
};
