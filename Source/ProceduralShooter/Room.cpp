// Fill out your copyright notice in the Description page of Project Settings.


#include "Room.h"


// Sets default values
ARoom::ARoom()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("root"));
	SetRootComponent(Root);
	DetectionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("DetectionBox"));
	DetectionBox->SetupAttachment(Root);
	DetectionBox->SetBoxExtent(FVector(500,500,500));
	DetectionBox->SetGenerateOverlapEvents(true);
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

bool ARoom::GetRoomOverlap() const
{
    if (!DetectionBox)
    {
        return false;
    }

    TArray<UPrimitiveComponent*> OverlappingComponents;
    DetectionBox->GetOverlappingComponents(OverlappingComponents);
    
    for (const auto Component : OverlappingComponents)
    {
        if (!Component || Component == DetectionBox)
        {
            continue;
        }
        
        UBoxComponent* OtherBox = Cast<UBoxComponent>(Component);
        if (!OtherBox)
        {
            continue;
        }
        
        AActor* OtherActor = OtherBox->GetOwner();
        if (!OtherActor)
        {
            continue;
        }
        
        ARoom* OtherRoom = Cast<ARoom>(OtherActor);
        if (!OtherRoom || OtherRoom == this)
        {
            continue;
        }
        
        // Verify this is the other room's main DetectionBox
        if (OtherBox != OtherRoom->DetectionBox)
        {
            continue;
        }
        
        
        FVector MyLocation = DetectionBox->GetComponentLocation();
        FVector OtherLocation = OtherBox->GetComponentLocation();
        float Distance = FVector::Distance(MyLocation, OtherLocation);
        
        // Only consider it an overlap if they're actually close enough
        if (Distance < MinOverlapDistance)
        {
            return true;
        }
    }
    return false;
}