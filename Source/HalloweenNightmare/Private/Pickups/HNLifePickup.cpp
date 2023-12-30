// Halloween Nightmare. All Rights Reserved.


#include "Pickups/HNLifePickup.h"
#include "HNPlayer.h"

void AHNLifePickup::Invoke()
{
    Super::Invoke();

    Player->AddLife(1);
}