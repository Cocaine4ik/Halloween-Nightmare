// Halloween Nightmare. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
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

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "User")
    FName UserName = "User";

public:
    FName GetUserName() const { return UserName; }
    void SetUserName(const FName Name) { UserName = Name; }
};