// Fill out your copyright notice in the Description page of Project Settings.


#include "Anchor.h"


// Sets default values for this component's properties
UAnchor::UAnchor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	NeighborDetector = CreateDefaultSubobject<UBoxComponent>(FName("NeighborDetector"));
	NeighborDetector->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
	NeighborDetector->SetBoxExtent(FVector(32.f, 32.f, 96.f));
	NeighborDetector->SetRelativeLocation(FVector(50, 0, 0));
	// ...
}


// Called when the game starts
void UAnchor::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAnchor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAnchor::CloseHole()
{
	GetWorld()->SpawnActor<AActor>(PlugActor, GetComponentLocation(), GetComponentRotation());
	DestroyComponent();
}

void UAnchor::DetectNeighbors()
{
	
}