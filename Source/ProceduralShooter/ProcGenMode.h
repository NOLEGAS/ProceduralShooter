// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Room.h"
#include "GameFramework/GameModeBase.h"
#include "Engine/World.h"
#include "ProcGenMode.generated.h"

/**
 * 
 */
UCLASS()
class PROCEDURALSHOOTER_API AProcGenMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TArray<UAnchor*> SpawnedAnchors;
	UPROPERTY()
	TArray<UAnchor*> RemovedAnchors;
	UPROPERTY()
	TArray<UAnchor*> NewRoomAnchors;
	//UPROPERTY()
	//const UAnchor* NewRoomAnchor;
	UPROPERTY()
	TArray<UAnchor*> Anchors;
	UPROPERTY()
	TArray<USpawner*> Spawners;
	
protected:
	virtual void StartPlay() override;
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<ARoom>> StartRooms;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<ARoom>> Rooms;
	UPROPERTY(EditAnywhere, meta = (ToolTip="Must not exceed Worlds amount", ClampMin="0"))
	int32 RoomCount;
	UPROPERTY(EditAnywhere, meta = (ClampMin="0"))
	int32 NeighborDetectionDistance = 100.0f;
	UPROPERTY(EditAnywhere, meta = (ClampMin="0"))
	int32 enemyCount;
	UPROPERTY(EditAnywhere, meta = (ClampMin="0"))
	int32 enemyCountVariation;
	UPROPERTY(Editanywhere, BlueprintReadWrite)
	int32 Seed;

};
