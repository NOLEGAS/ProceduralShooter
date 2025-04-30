// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcGenMode.h"



void AProcGenMode::StartPlay()
{
	Super::StartPlay();
	
	if (auto const World = GetWorld())
        {
            const auto RandomIndex = FMath::RandRange(0, StartRooms.Num() - 1);
    
            // Spawn the starting room
            ARoom* NewRoom = World->SpawnActor<ARoom>(StartRooms[RandomIndex]);
            TArray<UAnchor*> Anchors = NewRoom->GetAnchors();
            TArray<USpawner*> Spawners = NewRoom->GetSpawners();

			for (const auto Anchor : Anchors)
			{
				SpawnedAnchors.Add(Anchor);
			}
            for (int32 i = 1; i < RoomCount; i++)
            {
                if (Anchors.Num() > 0)
                {
                    // Pick a random anchor
                    const auto AnchorIndex = FMath::RandRange(0, Anchors.Num() - 1);
                    const UAnchor* SelectedAnchor = Anchors[AnchorIndex];
    
                    // Spawn a new room
                	/*TODO Rooms no longer spawn inside each other, but plugs still sometimes are missing. Need to debug more thoroughly to discover what causes it.*/
                    const auto RandomRoomIndex = FMath::RandRange(0, Rooms.Num() - 1);
                    NewRoom = World->SpawnActor<ARoom>(Rooms[RandomRoomIndex]);
    
                    if (NewRoom)
                    {
                    	TArray<USpawner*> NewRoomSpawners = NewRoom->GetSpawners();
                        // Find an anchor in the new room to match the selected anchor
                        if (TArray<UAnchor*> NewRoomAnchors = NewRoom->GetAnchors(); NewRoomAnchors.Num() > 0)
                        {
                        	for (const auto Anchor : NewRoomAnchors)
                        	{
                        		SpawnedAnchors.Add(Anchor);
                        	}
                            const auto SecondAnchorIndex = FMath::RandRange(0, NewRoomAnchors.Num() - 1);
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
                        			NewRoomAnchors.Empty();
                        			NewRoomSpawners.Empty();
                        			NewRoom->Destroy();
                        			//i--;
                        			continue;
                        	}
                        	
    
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
                        	// Add a new Spawner from the newly spawned room
                        	for (int32 a = 1; a < enemyCount + FMath::RandRange(-enemyCountVariation, enemyCountVariation); a++)
                        	{
								if (NewRoomSpawners.Num() > 0)
								{
									USpawner* FinalSpawner = NewRoomSpawners[FMath::RandRange(0, NewRoomSpawners.Num() - 1)];
									if (FinalSpawner && !Spawners.Contains(FinalSpawner))
									{
										Spawners.Add(FinalSpawner);	
									}
								}

                        	}
                        }
                    }
                }
                else
                {
                    // No more anchors to use
                    break;
                }
                
            }

			for (const auto AnchorA : SpawnedAnchors)
			{
				for (const auto AnchorB : SpawnedAnchors)
				{
					if (AnchorA == AnchorB) continue;
 
					const auto Distance = FVector::Distance(AnchorA->GetComponentLocation(), AnchorB->GetComponentLocation());
 
					if (Distance < NeighborDetectionDistance)
					{
						Anchors.Remove(AnchorA);
						Anchors.Remove(AnchorB);
						RemovedAnchors.Add(AnchorA);
						RemovedAnchors.Add(AnchorB);
						UE_LOG(LogTemp, Warning, TEXT("Because anchors were close to another: Removed %s from [%s] & %s from [%s]"), *AnchorA->GetName(), *AnchorA->GetAttachParentActor()->GetName(),
						*AnchorB->GetName(), *AnchorB->GetAttachParentActor()->GetName());
					}
				}
			}
			
	        //Tells remaining anchors to plug hole
	        for (const auto Anchor: Anchors)
	        {
	            Anchor->CloseHole();
	        }
			//Tells Spawners to spawn
			for (const auto Spawner: Spawners)
			{
				Spawner->Spawn();
			} 
        }
}