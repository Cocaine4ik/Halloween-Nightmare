// Halloween Nightmare. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/HNBasePickup.h"
#include "HNLifePickup.generated.h"

/**
 * 
 */
UCLASS()
class HALLOWEENNIGHTMARE_API AHNLifePickup : public AHNBasePickup
{
    GENERATED_BODY()

protected:
    virtual void Invoke() override;
};