// Halloween Nightmare. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/HNBasePickup.h"
#include "HNScorePickup.generated.h"

/**
 * 
 */
UCLASS()
class HALLOWEENNIGHTMARE_API AHNScorePickup : public AHNBasePickup
{
    GENERATED_BODY()

protected:
    virtual void Invoke() override;
};