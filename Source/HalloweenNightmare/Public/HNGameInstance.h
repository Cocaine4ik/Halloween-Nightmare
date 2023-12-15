// Halloween Nightmare. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "HNCoreTypes.h"
#include "HNGameInstance.generated.h"

UCLASS()
class HALLOWEENNIGHTMARE_API UHNGameInstance : public UGameInstance
{
    GENERATED_BODY()

public:
    FName GetStartupLevelName() const { return StartupLevelName; }
    FName GetMainMenuLevelName() const { return MainMenuLevelName; }
protected:
    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FName StartupLevelName = NAME_None;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FName MainMenuLevelName = NAME_None;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game")
    UDataAsset* UserNameDataAsset;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game")
    EHNLevel CurrentLevel = EHNLevel::Default;
    
public:
    FName GetUserName() const;
    void SetUserName(const FName Name);

    FORCEINLINE EHNLevel GetLevel() const { return CurrentLevel; }
    FORCEINLINE void SetLevel(EHNLevel Level) { CurrentLevel = Level; }
    FName GetLevelName() const;
};