// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPickup.h"
#include "ShooterCharacter.h"
#include "BuffComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"


AHealthPickup::AHealthPickup()
{
	PickupEffectComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PickupEffectComponent"));
	PickupEffectComponent->SetupAttachment(RootComponent);
}

void AHealthPickup::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 플레이어만 오버랩 실행하기
	if (!OtherActor->IsA(AShooterCharacter::StaticClass())) return;

	AShooterCharacter* Character = Cast<AShooterCharacter>(OtherActor);

	// 플레이어가 최대 체력일 때 오버랩 작동하지 않기
	if (Character->GetHealth() >= Character->GetMaxHealth()) return;

	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (Character)
	{
		UBuffComponent* Buff = Character->GetBuff();
		if (Buff)
		{
			Buff->Heal(HealAmount);
		}
	}

	Destroy();
}

void AHealthPickup::Destroyed()
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