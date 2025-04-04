// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Engine/LevelStreamingDynamic.h"
#include "ProcGenMode.generated.h"

/**
 * 
 */
UCLASS()
class PROCEDURALSHOOTER_API AProcGenMode : public AGameModeBase
{
	GENERATED_BODY()


protected:
	bool LoadLevel(TSoftObjectPtr<UWorld> worldToLoad);
	void TempMover(FVector& location);
	//Test both startplay and initgame
	virtual void StartPlay() override;
	//virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	
public:
	//Position of room
	UPROPERTY()
	int32 X = 0;
	UPROPERTY()
	int32 Y = 0;
	UPROPERTY()
	int32 Z = 0;
	UPROPERTY(editanywhere)
	FVector spawnLocation;
	UPROPERTY(editAnywhere)
	TArray<TSoftObjectPtr <UWorld>> Worlds;
	UPROPERTY(EditAnywhere, meta = (ToolTip="Must not exceed Worlds amount", ClampMin="0"))
	int32 roomCount;
	UPROPERTY(EditAnywhere)
	FVector moveAmount = {0, 0, 0};

};
