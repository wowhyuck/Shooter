﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "AmmoType.h"
#include "Engine/DataTable.h"
#include "WeaponType.h"
#include "Weapon.generated.h"


USTRUCT(BlueprintType)
struct FWeaponDataTable : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAmmoType AmmoType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 WeaponAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MagazineCapacity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundCue* PickupSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundCue* EquipSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* ItemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* InventoryIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* AmmoIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInstance* MaterialInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaterialIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ClipBoneName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ReloadMontageSection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UAnimInstance> AnimBP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* CrosshairsMiddle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* CrosshairsLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* CrosshairsRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* CrosshairsBottom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* CrosshairsTop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AutoFireRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundCue* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName BoneToHide;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bAutomatic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HeadShotDamage;
};

/**
 * 
 */
UCLASS()
class SHOOTER_API AWeapon : public AItem
{
	GENERATED_BODY()
	
public:
	AWeapon();

	virtual void Tick(float DeltaTime) override;

protected:
	void StopFalling();
	
	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void BeginPlay() override;

	void FinishMovingSlide();
	void UpdateSlideDisplacement();

private:
	FTimerHandle ThrowWeaponTimer;
	float ThrowWeaponTime;
	bool bFalling;

	// 무기의 탄약 개수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties", meta = (AllowPrivateAccess = "true"))
	int32 Ammo;

	// 갖고 있는 무기의 탄창 최대수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties", meta = (AllowPrivateAccess = "true"))
	int32 MagazineCapacity;

	// 무기 타입
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties", meta = (AllowPrivateAccess = "true"))
	EWeaponType WeaponType;

	// 무기의 탄약 타입
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties", meta = (AllowPrivateAccess = "true"))
	EAmmoType AmmoType;

	// 장전 몽타주 섹션의 FName
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties", meta = (AllowPrivateAccess = "true"))
	FName ReloadMontageSection;

	// 장전 중에 탄창이 움직일 때 true
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon Properties", meta = (AllowPrivateAccess = "true"))
	bool bMovingClip;

	// 탄창 bone의 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties", meta = (AllowPrivateAccess = "true"))
	FName ClipBoneName;

	// 무기 데이터 테이블
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
	UDataTable* WeaponDataTable;

	int32 PreviousMaterialIndex;

	// 무기 조준점 Texture
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
	UTexture2D* CrosshairsMiddle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
	UTexture2D* CrosshairsLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
	UTexture2D* CrosshairsRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
	UTexture2D* CrosshairsBottom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
	UTexture2D* CrosshairsTop;

	// 연사 속도
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
	float AutoFireRate;

	// BarrelSocket에서 particle system 불러오기
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
	class UParticleSystem* MuzzleFlash;

	// 발사 소리
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
	USoundCue* FireSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
	FName BoneToHide;

	// 권총 발사 중에 뒤로 밀리는 slide의 양
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pistol", meta = (AllowPrivateAccess = "true"))
	float SlideDisplacement;

	// SlideDisplacement의 Curve
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pistol", meta = (AllowPrivateAccess = "true"))
	UCurveFloat* SlideDisplacementCurve;

	// SlideDisplacement의 업데이트를 위한 Timer Handle
	FTimerHandle SlideTimer;

	// 권총 발사 중에 slide가 분리되는 중의 시간
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pistol", meta = (AllowPrivateAccess = "true"))
	float SlideDisplacementTime;

	// slide가 움직일 때 true
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pistol", meta = (AllowPrivateAccess = "true"))
	bool bMovingSlide;

	// slide가 이동할 수 있는 최대 거리
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pistol", meta = (AllowPrivateAccess = "true"))
	float MaxSlideDisplacement;

	// 권총 반동 최대 회전
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pistol", meta = (AllowPrivateAccess = "true"))
	float MaxRecoilRotation;

	// 권총 발사 중 권총 회전량
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pistol", meta = (AllowPrivateAccess = "true"))
	float RecoilRotation;

	// 연사일 때 true
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties", meta = (AllowPrivateAccess = "true"))
	bool bAutomatic;

	// 공격력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties", meta = (AllowPrivateAccess = "true"))
	float Damage;

	// 헤드샷 공격력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties", meta = (AllowPrivateAccess = "true"))
	float HeadShotDamage;

public:
	// 장착무기 던지기
	void ThrowWeapon();

	FORCEINLINE int32 GetAmmo() const { return Ammo; }
	FORCEINLINE int32 GetMagazineCapacity() const { return MagazineCapacity; }
	
	// 캐릭터가 총을 쏠 때 호출하기
	void DecrementAmmo();

	FORCEINLINE EWeaponType GetWeaponType() const { return WeaponType; }
	FORCEINLINE EAmmoType GetAmmoType() const { return AmmoType; }
	FORCEINLINE FName GetReloadMontageSection() const { return ReloadMontageSection; }
	FORCEINLINE void SetReloadMontageSection(FName Name) { ReloadMontageSection = Name; }
	FORCEINLINE FName GetClipBoneName() const { return ClipBoneName; }
	FORCEINLINE void SetClipBoneName(FName Name) { ClipBoneName = Name; }
	FORCEINLINE float GetAutoFireRate() const { return AutoFireRate; }
	FORCEINLINE UParticleSystem* GetMuzzleFlash() const { return MuzzleFlash; }
	FORCEINLINE USoundCue* GetFireSound() const { return FireSound; }
	FORCEINLINE bool GetAutomatic() const { return bAutomatic; }
	FORCEINLINE float GetDamage() const { return Damage; }
	FORCEINLINE float GetHeadShotDamage() const { return HeadShotDamage; }

	void StartSlideTimer();

	void ReloadAmmo(int32 Amount);

	FORCEINLINE void SetMovingClip(bool Move) { bMovingClip = Move; }

	bool ClipIsFull();
};
