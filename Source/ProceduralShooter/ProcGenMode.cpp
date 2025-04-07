// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcGenMode.h"



void AProcGenMode::StartPlay()
{
	for (int i = 0; i < roomCount; i++)
	{
		SpawnRoom(Rooms[i]);
		TempMover(moveAmount);
	}
}

void AProcGenMode::SpawnRoom(const TSoftClassPtr<ARoom>& RoomToLoad) const
{
	GetWorld()->SpawnActor<ARoom>(RoomToLoad.Get(),spawnLocation,spawnRotation);
}


//Temporary solution for moving BP_ProcGen
void AProcGenMode::TempMover(const FVector& Location)
{
	spawnLocation += Location;
}