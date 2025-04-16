// Fill out your copyright notice in the Description page of Project Settings.


#include "Room.h"


// Sets default values
ARoom::ARoom()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARoom::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

TArray<UAnchor*> ARoom::GetAnchors() const
{
	auto Anchors = TArray<UAnchor*>();
	
	for (auto const Child : GetComponents())
	{
		if (auto Anchor = Cast<UAnchor>(Child))
		{
			Anchors.Add(Anchor);
		}
	}
	
	return Anchors;
}

TArray<USpawner*> ARoom::GetSpawners() const
{
	auto Spawners = TArray<USpawner*>();
	
	for (auto const Child : GetComponents())
	{
		if (auto Spawner = Cast<USpawner>(Child))
		{
			Spawners.Add(Spawner);
		}
	}
	
	return Spawners;
}