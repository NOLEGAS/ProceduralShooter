// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcGenMode.h"

void AProcGenMode::BeginPlay()
{
	Super::BeginPlay();
	if (auto const World = GetWorld())
        {
			SeedGameInstance = Cast<UProcGenGameInstance>(World->GetGameInstance());
			//Sets seed for generation and if the seed variable is set in the header then it uses that. (For testing)
			if (SeedGameInstance)
			{
				RandomSeed = SeedGameInstance->GetSeed();
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Failed to set seed"));
			}
			FRandomStream RandomStream(RandomSeed);
            const auto RandomIndex = RandomStream.RandRange(0, StartRooms.Num() - 1);
			UE_LOG(LogTemp, Warning, TEXT("Seed: %d"), RandomSeed);
    
            // Spawn the starting room
            ARoom* NewRoom = World->SpawnActor<ARoom>(StartRooms[RandomIndex]);
            Anchors = NewRoom->GetAnchors();
            Spawners = NewRoom->GetSpawners();
			RoomsSpawned.Add(NewRoom);

			for (const auto Anchor : Anchors)
			{
				SpawnedAnchors.Add(Anchor);
			}
            for (int32 i = 1; i < RoomCount; i++)
            {
                if (Anchors.Num() > 0)
                {
                    // Pick a random anchor
                    const auto AnchorIndex = RandomStream.RandRange(0, Anchors.Num() - 1);
                    const UAnchor* SelectedAnchor = Anchors[AnchorIndex];
    
                    // Spawn a new room
                    const auto RandomRoomIndex = RandomStream.RandRange(0, Rooms.Num() - 1);
                    NewRoom = World->SpawnActor<ARoom>(Rooms[RandomRoomIndex]);
    
                    if (NewRoom)
                    {
                    	TArray<USpawner*> NewRoomSpawners = NewRoom->GetSpawners();
                        // Find an anchor in the new room to match the selected anchor
                        if (NewRoomAnchors = NewRoom->GetAnchors(); NewRoomAnchors.Num() > 0)
                        {
                        	
                            const auto SecondAnchorIndex = RandomStream.RandRange(0, NewRoomAnchors.Num() - 1);
                            const UAnchor* NewRoomAnchor = NewRoomAnchors[SecondAnchorIndex];
    
                            // Calculate the rotation so that the anchors face each other
                            const FRotator SelectedAnchorRotation = SelectedAnchor->GetComponentRotation();
                            const FRotator NewRoomAnchorRotation = NewRoomAnchor->GetComponentRotation();
                            const FRotator DesiredRotation = (SelectedAnchorRotation + FRotator(0, 180, 0)) - NewRoomAnchorRotation;
                            NewRoom->AddActorWorldRotation(DesiredRotation);
    
                            // Calculate the new room's position so that the anchors match
                            const FVector NewRoomAnchorOffset = NewRoomAnchor->GetComponentLocation() - NewRoom->GetActorLocation();
                            const FVector Offset = SelectedAnchor->GetComponentLocation() - NewRoomAnchorOffset;
                            NewRoom->SetActorLocation(NewRoom->GetActorLocation() + Offset);
                        	//Check if there is a room already there
                        	if (IsValid(NewRoom) && NewRoom->GetRoomOverlap() && NewRoom)
                        	{
                        			NewRoom->Destroy();
                        			i--;
                        			continue;
                        	}
                        	
                        	for (const auto Anchor : NewRoomAnchors)
                        	{
                        		SpawnedAnchors.Add(Anchor);
                        	}
                        	//Adds new room to RoomsSpawned
                        	RoomsSpawned.Add(NewRoom);
    
                            // Remove the used anchor
                            Anchors.RemoveAt(AnchorIndex);
    
                            // Add new anchors from the newly spawned room, excluding the matched anchor
                            for (UAnchor* Anchor : NewRoomAnchors)
                            {
                                if (Anchor != NewRoomAnchor)
                                {
                                    Anchors.Add(Anchor);
                                }
                            }
                        	
                        	
                        		// Add the Spawners from the newly spawned room
                        		if (NewRoomSpawners.Num() > 0)
                        		{
                        			for (int32 a = 1; a < NewRoomSpawners.Num(); a++)
                        			{
                        				if (!Spawners.Contains(NewRoomSpawners[a]))
                        				Spawners.Add(NewRoomSpawners[a]);
                        			}
                        		}
                        }
                    }
                }
                else
                {
                    // No more anchors to use
                	UE_LOG(LogTemp, Warning, TEXT("No anchors to use"));
                    break;
                }
                
            }

			 
        }
}


void AProcGenMode::StartPlay()
{
	Super::StartPlay();
	
	
	for (const auto AnchorA : SpawnedAnchors)
	{
		for (const auto AnchorB : SpawnedAnchors)
		{
			if (AnchorA == AnchorB) continue;
 
			const auto Distance = FVector::Distance(AnchorA->GetComponentLocation(), AnchorB->GetComponentLocation());
 
			if (Distance < NeighborDetectionDistance)
			{
				//Removes AnchorA and AnchorB from the array of anchors that get closehole called
				Anchors.Remove(AnchorA);
				Anchors.Remove(AnchorB);
				RemovedAnchors.Add(AnchorA);
				RemovedAnchors.Add(AnchorB);
			}
		}
	}
	//Removes Detectionboxes used for room collision from rooms
	for (const auto Room : RoomsSpawned)
	{
		Room->DetectionBox->DestroyComponent();
	}
	//Tells remaining anchors to plug hole
	for (const auto Anchor: Anchors)
	{
		Anchor->CloseHole();
	}

	FRandomStream RandomStream(RandomSeed);
	
	//Tells Spawners to spawn (Pickups)
	for (int32 b = 1; b < PickupCount + RandomStream.RandRange(-PickupCountVariation, PickupCountVariation); b++)
	{
		if (Spawners.Num() > 0)
		{
			int32 MaxIterations = 0;
			auto Spawner = Spawners[RandomStream.RandRange(0, Spawners.Num() - 1)];
			while (Spawner->IsEnemy || Spawner->isUsed)
			{
				Spawner = Spawners[RandomStream.RandRange(0, Spawners.Num() - 1)];
				MaxIterations++;
				if (MaxIterations > SpawnProbeIterations)
				{
					UE_LOG(LogTemp, Warning, TEXT("Pickup Spawner not found"));
					break;
				}
			}
			if (MaxIterations < SpawnProbeIterations)
			{
				Spawner->Spawn();
			}
		}
		
		
	}
	//Tells Spawners to spawn (Enemies)
	for (int32 b = 1; b < enemyCount + RandomStream.RandRange(-enemyCountVariation, enemyCountVariation); b++)
	{
		if (Spawners.Num() > 0)
		{
			int32 MaxIterations = 0;
			auto Spawner = Spawners[RandomStream.RandRange(0, Spawners.Num() - 1)];
			while (!Spawner->IsEnemy || Spawner->isUsed)
			{
				Spawner = Spawners[RandomStream.RandRange(0, Spawners.Num() - 1)];
				MaxIterations++;
				if (MaxIterations > SpawnProbeIterations)
				{
					UE_LOG(LogTemp, Warning, TEXT("Enemy Spawner not found"));
					break;
				}
			}
			if (MaxIterations < SpawnProbeIterations)
			{
				Spawner->Spawn();
			}
		}
	}
    
}