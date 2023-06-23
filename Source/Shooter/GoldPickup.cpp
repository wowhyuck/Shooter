﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "GoldPickup.h"
#include "ShooterCharacter.h"
#include "BuffComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

AGoldPickup::AGoldPickup() :
	GoldAmount(10)
{
	PickupEffectComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PickupEffectComponent"));
	PickupEffectComponent->SetupAttachment(RootComponent);
}

void AGoldPickup::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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
			Buff->TakeGold(GoldAmount);
		}
	}

	Destroy();
}

void AGoldPickup::Destroyed()
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
