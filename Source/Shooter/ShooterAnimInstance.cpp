// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAnimInstance.h"
#include "ShooterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UShooterAnimInstance::UpdateAnimationProperties(float deltaTime)
{
	if (ShooterCharacter == nullptr)
	{
		ShooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());
	}

	if (ShooterCharacter)
	{
		// 캐릭터 이동 속도
		FVector velocity{ ShooterCharacter->GetVelocity() };
		velocity.Z = 0;
		speed = velocity.Size();

		// 캐릭터가 공중에 떠 있는지?
		bIsAir = ShooterCharacter->GetCharacterMovement()->IsFalling();

		// 캐릭터가 움직이는지?
		if (ShooterCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f)
		{
			bIsAccelerating = true;
		}
		else
		{
			bIsAccelerating = false;
		}

		FRotator AimRotation = ShooterCharacter->GetBaseAimRotation();
		FRotator MovementRotation =
			UKismetMathLibrary::MakeRotFromX(
				ShooterCharacter->GetVelocity());
		MovementOffsetYaw = UKismetMathLibrary::NormalizedDeltaRotator(
			MovementRotation,
			AimRotation).Yaw;

		//FString RotationMessage = FString::Printf(
		//	TEXT("Base Aim Rotation: %f"), 
		//	AimRotation.Yaw);

		//FString MovementRotationMessage = FString::Printf(
		//	TEXT("Base Aim Rotation: %f"),
		//	MovementRotation.Yaw);

		//FString OffsetMessage = FString::Printf(
		//	TEXT("Movement Offset Yaw: %f"),
		//	MovementOffsetYaw);

		//if (GEngine)
		//{
		//	GEngine->AddOnScreenDebugMessage(1, 0.f, FColor::White, OffsetMessage);
		//}
	}
}

void UShooterAnimInstance::NativeInitializeAnimation()
{
	ShooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());



}
