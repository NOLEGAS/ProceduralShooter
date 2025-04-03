// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelStreamingDynamic.h"
#include "Anchor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Containers/List.h"
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
	virtual bool LoadLevel(TSoftObjectPtr<UWorld> worldToLoad);
	virtual void TempMover(FVector& location);

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
	UPROPERTY(editAnywhere)
	TArray<UWorld*> Worlds;
	UPROPERTY(EditAnywhere, meta = (ToolTip="Must not exceed Worlds amount", ClampMin="0"))
	int32 roomCount;
	UPROPERTY(EditAnywhere)
	FVector moveAmount = FVector{0, 1000, 0};
};
