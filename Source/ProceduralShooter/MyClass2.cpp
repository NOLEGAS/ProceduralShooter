// Fill out your copyright notice in the Description page of Project Settings.


#include "MyClass2.h"


// Sets default values
AMyClass2::AMyClass2()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyClass2::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyClass2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

