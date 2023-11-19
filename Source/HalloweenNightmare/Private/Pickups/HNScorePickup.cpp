// Halloween Nightmare. All Rights Reserved.


#include "Pickups/HNScorePickup.h"
#include "HNGameMode.h"

void AHNScorePickup::Invoke()
{
    Super::Invoke();

    if (!GetWorld()) return;

    const auto GameMode = Cast<AHNGameMode>(GetWorld()->GetAuthGameMode());
    GameMode->AddScore(1);
}