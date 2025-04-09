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


protected:
	virtual void StartPlay() override;
	void SpawnRoom(const TSoftClassPtr<ARoom>& RoomToLoad) const;
	

	
public:
	//Position of room
	UPROPERTY()
	int32 X = 0;
	UPROPERTY()
	int32 Y = 0;
	UPROPERTY()
	int32 Z = 0;
	
	UPROPERTY()
	FVector spawnLocation;
	UPROPERTY()
	FRotator spawnRotation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<ARoom>> Rooms;
	UPROPERTY(EditAnywhere, meta = (ToolTip="Must not exceed Worlds amount", ClampMin="0"))
	int32 roomCount;
	UPROPERTY(EditAnywhere)
	FVector moveAmount = {0, 0, 0};
	

};
