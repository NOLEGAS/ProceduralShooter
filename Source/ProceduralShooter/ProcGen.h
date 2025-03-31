// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chunk.h"
#include "GameFramework/Actor.h"
#include "ProcGen.generated.h"

UCLASS()
class PROCEDURALSHOOTER_API AProcGen : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProcGen();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Position of room
	UPROPERTY()
	int32 X = 0;
	UPROPERTY()
	int32 Y = 0;
	UPROPERTY()
	int32 Z = 0;
	UPROPERTY()
	int32 roomCount = 2;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UChunk> chunkToSpawn;
};
