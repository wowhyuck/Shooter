﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedPickup.h"
#include "ShooterCharacter.h"
#include "BuffComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"


ASpeedPickup::ASpeedPickup() :
	BaseSpeedBuff(1600.f),
	CrouchSpeedBuff(850.f),
	SpeedBuffTime(10.f)
{
	PickupEffectComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PickupEffectComponent"));
	PickupEffectComponent->SetupAttachment(RootComponent);
}

void ASpeedPickup::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 플레이어만 오버랩 실행하기
	if (!OtherActor->IsA(AShooterCharacter::StaticClass())) return;

	AShooterCharacter* Character = Cast<AShooterCharacter>(OtherActor);

	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (Character)
	{
		UBuffComponent* Buff = Character->GetBuff();
		if (Buff)
		{
			Buff->BuffSpeed(BaseSpeedBuff, CrouchSpeedBuff, SpeedBuffTime);
		}
	}

	Destroy();
}

void ASpeedPickup::Destroyed()
{
	if (PickupEffect)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			this,
			PickupEffect,
			GetActorLocation(),
			GetActorRotation());
	}

	Super::Destroyed();
}
