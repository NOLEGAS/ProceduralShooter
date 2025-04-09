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

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<ARoom>> Rooms;
	UPROPERTY(EditAnywhere, meta = (ToolTip="Must not exceed Worlds amount", ClampMin="0"))
	int32 RoomCount;
};
