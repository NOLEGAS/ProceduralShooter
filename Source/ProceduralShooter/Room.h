// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Anchor.h"
#include "Spawner.h"
#include "GameFramework/Actor.h"
#include "Room.generated.h"

UCLASS()
class PROCEDURALSHOOTER_API ARoom : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARoom();
	UFUNCTION()
	TArray<UAnchor*> GetAnchors() const;
	UFUNCTION()
	TArray<USpawner*> GetSpawners() const;
	UFUNCTION()
	bool GetRoomOverlap() const;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
	UBoxComponent* DetectionBox;
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	UPROPERTY(EditAnywhere)
	float MinOverlapDistance = 700.0f; //Adjust this value based on room sizes
};
