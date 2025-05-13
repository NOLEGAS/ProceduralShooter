// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcGenGameInstance.h"


int32 UProcGenGameInstance::GetSeed()
{
	return InstanceSeed;
}

void UProcGenGameInstance::SetSeed(int32 SeedToSet)
{
	InstanceSeed = SeedToSet;
}

int32 UProcGenGameInstance::GenerateSeed()
{
	return InstanceSeed != 0 ? InstanceSeed : FMath::Rand();
}

void UProcGenGameInstance::OnStart()
{
	InstanceSeed = GenerateSeed();
	InstanceRoomCount = 10;
}

int32 UProcGenGameInstance::GetRoomCount() const
{
	return InstanceRoomCount;
}
void UProcGenGameInstance::SetRoomCount(int32 RoomCountToSet)
{
	InstanceRoomCount = RoomCountToSet;
}