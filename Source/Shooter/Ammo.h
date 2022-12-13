// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "AmmoType.h"
#include "Ammo.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API AAmmo : public AItem
{
	GENERATED_BODY()
public:
	AAmmo();
	
	virtual void Tick(float DeltaTime) override;

protected:
	
	virtual void BeginPlay() override;

	// SetItemPropertise Override -> AmmoMesh 특성에 맞게 설정하기
	virtual void SetItemProperties(EItemState State) override;

private:
	// 탄약 메쉬
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ammo, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* AmmoMesh;

	// 탄약 타입
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ammo, meta = (AllowPrivateAccess = "true"))
	EAmmoType AmmoType;
	
public:
	FORCEINLINE UStaticMeshComponent* GetMesh() const { return AmmoMesh; }
	FORCEINLINE EAmmoType GetAmmoType() const { return AmmoType; }
};
