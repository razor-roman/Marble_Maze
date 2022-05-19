// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTablePawn2.h"

AMyTablePawn2::AMyTablePawn2()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoardVisualAsset(TEXT("StaticMesh'/Game/Meshes/maze.maze'"));
	if(BoardVisualAsset.Succeeded())
	{ 
		Board->SetStaticMesh(BoardVisualAsset.Object);
	}
	Board->SetRelativeScale3D(FVector(10,10,10));
	
}
