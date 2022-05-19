// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "TablePawn.generated.h"

class AActorToSpawn;
class UInputComponent;
UCLASS()
class LABIRINTHTABLE_C_API ATablePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATablePawn();
	UPROPERTY()
	USceneComponent* Root;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Board;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BoardTop;	
	UPROPERTY(EditAnywhere)
	UArrowComponent* Arrow;
	UPROPERTY(EditAnywhere)
	UBoxComponent* Collider;
	UPROPERTY()	
	UCameraComponent* Camera;
	
	
	void SpawnActor();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void MoveAxisX(float Axis);
	void MoveAxisY(float Axis);
	float AxisX;
	float AxisY;
	float AngleMax = 15.0f;
	float AngleMin = -15.0f;
	float RotationSpeed=10.0f;

	FVector currentCameraLocation;
	FVector cameraLocation;
	FQuat cameraQuat;
	
	UPROPERTY()
	AActorToSpawn* ball;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
