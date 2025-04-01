// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcGen.h"

#include "Engine/LevelStreamingDynamic.h"


// Sets default values
AProcGen::AProcGen()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}


// Called when the game starts or when spawned
void AProcGen::BeginPlay()
{
	bool success = false;
	Super::BeginPlay();
	for (int i = 0; i < roomCount; i++)
	{
		ULevelStreamingDynamic::LoadLevelInstanceBySoftObjectPtr(GetWorld(), Worlds[i], GetTransform(), success);
	}

}

// Called every frame
void AProcGen::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}