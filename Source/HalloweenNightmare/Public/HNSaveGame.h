// Halloween Nightmare. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "HNCoreTypes.h"
#include "HNSaveGame.generated.h"

UCLASS()
class HALLOWEENNIGHTMARE_API UHNSaveGame : public USaveGame
{
    GENERATED_BODY()

protected:
    UPROPERTY(VisibleAnywhere)
    TArray<FHNScoresData> ScoresDataArray;

    UPROPERTY(VisibleAnywhere)
    FName UserName = "User";

public:
    FORCEINLINE TArray<FHNScoresData> GetScoresDataArray() const { return ScoresDataArray; }
    FORCEINLINE void AddScoresData(const FHNScoresData& Data) {ScoresDataArray.Add(Data); }
    
    FORCEINLINE FName GetUserName() const { return UserName; }
    FORCEINLINE void SetUserName(const FName& Name) { UserName = Name; } 
};