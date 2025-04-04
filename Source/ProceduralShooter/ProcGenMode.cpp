// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcGenMode.h"



void AProcGenMode::StartPlay()
{
	for (int i = 0; i < roomCount; i++)
	{
		LoadLevel(Worlds[i]);
		TempMover(moveAmount);
	}
}

bool AProcGenMode::LoadLevel(TSoftObjectPtr<UWorld> worldToLoad)
{
	bool success = false;
	ULevelStreamingDynamic::LoadLevelInstanceBySoftObjectPtr(GetWorld(), worldToLoad, FTransform(spawnLocation), success);
	return success;
}

//Temporary solution for moving BP_Procgen
void AProcGenMode::TempMover(FVector& location)
{
	spawnLocation += location;
}