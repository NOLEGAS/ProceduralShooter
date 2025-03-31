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
	
}

// Called every frame
void AProcGen::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProcGen::OnConstruction(const FTransform& Transform)
{
	//Spawns chunk actor at transform of procgen
	//Possible issue with externally referencing Ulevel Chunk
	GetWorld()->SpawnActor<AProcGen>(chunkToSpawn, Transform);
}