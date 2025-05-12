// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ProcGenGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROCEDURALSHOOTER_API UProcGenGameInstance : public UGameInstance
{
	GENERATED_BODY()

private:
	virtual void Init() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 InstanceSeed;
	UFUNCTION(BlueprintCallable)
	int32 GetSeed() ;
	UFUNCTION(BlueprintCallable)
	void SetSeed(int32 SeedToSet);
	UFUNCTION(BlueprintCallable)
	int32 GenerateSeed();
};

