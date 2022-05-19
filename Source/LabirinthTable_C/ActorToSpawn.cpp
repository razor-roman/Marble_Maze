// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorToSpawn.h"

#include "TablePawn.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AActorToSpawn::AActorToSpawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	ParticleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComp"));

	StaticMeshComp->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepRelativeTransform);
	ParticleComp->AttachToComponent(StaticMeshComp,FAttachmentTransformRules::KeepRelativeTransform);

	StaticMeshComp->SetRelativeLocation(FVector(0.0, 0.0, -12.0f));
	StaticMeshComp->SetRelativeScale3D(FVector(1, 1, 1));
	StaticMeshComp->SetSimulatePhysics(true);
	//static ConstructorHelpers::FObjectFinder<UMaterial>SphereMeshMaterial(TEXT("Material'/Engine/EditorMeshes/ColorCalibrator/M_ChromeBall.M_ChromeBall'"));
	//StaticMeshComp->SetMaterial(0,SphereMeshMaterial.Object);
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMeshAsset(TEXT("StaticMesh'/Engine/VREditor/BasicMeshes/SM_Ball_01.SM_Ball_01'"));
	StaticMeshComp->SetStaticMesh(SphereMeshAsset.Object);
	StaticMeshComp->BoundsScale=4;
	StaticMeshComp->BodyInstance.bOverrideMass=true;
	StaticMeshComp->BodyInstance.SetMassOverride(1000.0f);
	
	//StaticMeshComp->SetConstraintMode(EDOFMode::SixDOF);
	static ConstructorHelpers::FObjectFinder<UParticleSystem>ParticleCompAsset(TEXT("ParticleSystem'/Engine/Tutorial/SubEditors/TutorialAssets/TutorialParticleSystem.TutorialParticleSystem'"));
	ParticleComp->SetTemplate(ParticleCompAsset.Object);
	ParticleComp->SetRelativeScale3D(FVector(0.1f,0.1f,0.1f));
}

// Called when the game starts or when spawned
void AActorToSpawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AActorToSpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

