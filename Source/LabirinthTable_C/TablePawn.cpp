// Fill out your copyright notice in the Description page of Project Settings.


#include "TablePawn.h"

#include <DirectXMath.h>

#include "ActorToSpawn.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATablePawn::ATablePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	Board = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Board"));
	BoardTop = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoardTop"));
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoardVisualAsset(TEXT("StaticMesh'/Game/Box_Brush38_StaticMesh.Box_Brush38_StaticMesh'"));
	if(BoardVisualAsset.Succeeded())
	{ 
		Board->SetStaticMesh(BoardVisualAsset.Object);
	}
	
	RootComponent=Root;
	Board->SetupAttachment(Root);
	Camera->SetupAttachment(Root);	
	Arrow->SetupAttachment(Root);
	Collider->SetupAttachment(Root);
	Collider->SetupAttachment(Root);
		
	Board->SetRelativeScale3D(FVector(5,5,5));
	
	Arrow->SetRelativeLocation(FVector(400,1880,250));
	Arrow->SetRelativeRotation(FRotator(0,90,0));

	Collider->SetRelativeScale3D(FVector(10,1,1));
	Collider->SetRelativeLocation(FVector(-500,-950,100));

	Camera->SetRelativeRotation(FRotator(-90,0,0));
}

// Called when the game starts or when spawned
void ATablePawn::BeginPlay()
{
	Super::BeginPlay();
	SpawnActor();

	
}

void ATablePawn::MoveAxisX(float AxisValue)
{
	AxisX=AxisValue;
}

void ATablePawn::MoveAxisY(float AxisValue)
{
	AxisY=AxisValue;
}

void ATablePawn::SpawnActor()
{
	FVector SpawnLocation = Arrow->GetRelativeLocation();
	FRotator SpawnRotation = Arrow->GetRelativeRotation();
	ball = GetWorld()->SpawnActor<AActorToSpawn>(SpawnLocation,SpawnRotation);
	
}


// Called every frame
void ATablePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*float mouseX;
	float mouseY;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(mouseX, mouseY);
	UE_LOG(LogTemp, Warning, TEXT("Mouse Location: %f, %f"), mouseX, mouseY);*/

	FRotator currentRotation = Board->GetRelativeRotation();	
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%f"),NewY));
	float newRotationPitch= currentRotation.Pitch+AxisY*RotationSpeed*DeltaTime;
	float newRotationRoll= currentRotation.Roll+AxisX*RotationSpeed*DeltaTime;
	newRotationPitch = FMath::Clamp(newRotationPitch,AngleMin,AngleMax);
	newRotationRoll = FMath::Clamp(newRotationRoll,AngleMin,AngleMax);
	
	FRotator rotatePosition =FRotator(newRotationPitch,0,newRotationRoll);	
	Board->SetRelativeRotation(rotatePosition);
	
	FVector ballLocation = ball->GetActorLocation();
	if(ballLocation.Z<=-500)
	{
		ball->SetActorLocation(FVector(400,1880,250));
		Board->SetRelativeRotation(FRotator(0,0,0));
		ball->Reset();
	}
	Camera->SetRelativeLocation(FVector(ballLocation.X,ballLocation.Y,ballLocation.Z+3000),true,nullptr,ETeleportType::ResetPhysics);	
}

// Called to bind functionality to input
void ATablePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (InputComponent)
	{
		// Bind an action to it
		InputComponent->BindAxis("MouseX",this,&ATablePawn::MoveAxisX);
		InputComponent->BindAxis("MouseY",this,&ATablePawn::MoveAxisY);
	}
	else
	{
	UE_LOG(LogTemp, Warning, TEXT("Error Input Component"));		
	}
	
}

