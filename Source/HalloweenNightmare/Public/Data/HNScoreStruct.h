// Halloween Nightmare. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "HNScoreStruct.generated.h"

USTRUCT(BlueprintType)
struct FHNScoreStruct : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()
    
    UPROPERTY(BlueprintReadOnly, Category = "Data")
    FName UserName;

    UPROPERTY(BlueprintReadOnly, Category = "Data")
    int32 Score;

    UPROPERTY(BlueprintReadOnly, Category = "Data")
    FDateTime DateTime;
};