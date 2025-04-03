// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcGen.h"


// Sets default values
AProcGen::AProcGen()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}


// Called when the game starts or when spawned
void AProcGen::BeginPlay()
{
	
	Super::BeginPlay();
	for (int i = 0; i < roomCount; i++)
	{
		LoadLevel(Worlds[i]);
		TempMover(moveAmount);
	}

}

// Called every frame
void AProcGen::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AProcGen::LoadLevel(TSoftObjectPtr<UWorld> worldToLoad)
{
	bool success = false;
	ULevelStreamingDynamic::LoadLevelInstanceBySoftObjectPtr(GetWorld(), worldToLoad, GetTransform(), success);
	return success;
}

//Temporary solution for moving BP_Procgen
void AProcGen::TempMover(FVector& location)
{
	SetActorLocation(GetActorLocation() + location);
}