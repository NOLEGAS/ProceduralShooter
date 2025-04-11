// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcGenMode.h"



void AProcGenMode::StartPlay()
{
	Super::StartPlay();
	
	if (auto const World = GetWorld())
        {
            const auto RandomIndex = FMath::RandRange(0, Rooms.Num() - 1);
    
            // Spawn the starting room
            auto NewRoom = World->SpawnActor<ARoom>(Rooms[RandomIndex]);
            TArray<UAnchor*> Anchors = NewRoom->GetAnchors();
    
            for (int32 i = 1; i < RoomCount; i++)
            {
                if (Anchors.Num() > 0)
                {
                    // Pick a random anchor
                    const auto AnchorIndex = FMath::RandRange(0, Anchors.Num() - 1);
                    const UAnchor* SelectedAnchor = Anchors[AnchorIndex];
    
                    // Spawn a new room
                    const auto RandomRoomIndex = FMath::RandRange(0, Rooms.Num() - 1);
                    NewRoom = World->SpawnActor<ARoom>(Rooms[RandomRoomIndex]);
    
                    if (NewRoom)
                    {
                        // Find an anchor in the new room to match the selected anchor
                        if (const TArray<UAnchor*> NewRoomAnchors = NewRoom->GetAnchors(); NewRoomAnchors.Num() > 0)
                        {
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
                        }
                    }
                }
                else
                {
                    // No more anchors to use
                    break;
                }
                //Tells remaining anchors to plug hole
                //for (const auto Anchor: Anchors)
                //{
                //    Anchor->CloseHole();
                //}
            }
        }
}