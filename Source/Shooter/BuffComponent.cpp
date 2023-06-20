// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffComponent.h"
#include "ShooterCharacter.h"


UBuffComponent::UBuffComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UBuffComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UBuffComponent::Heal(float HealAmount)
{
	Character->SetHealth(FMath::Clamp(Character->GetHealth() + HealAmount, 0.f, Character->GetMaxHealth()));
}

void UBuffComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

