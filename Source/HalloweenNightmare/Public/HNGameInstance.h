// Halloween Nightmare. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "HNCoreTypes.h"
#include "HNGameInstance.generated.h"

class UHNSaveGame;
class USaveGame;

UCLASS()
class HALLOWEENNIGHTMARE_API UHNGameInstance : public UGameInstance
{
    GENERATED_BODY()

public:
    FOnSaveUserNameSignature OnSaveUserName;
    FOnSaveScoresSignature OnSaveScores;
    
    FName GetStartupLevelName() const { return StartupLevelName; }
    FName GetMainMenuLevelName() const { return MainMenuLevelName; }
protected:
    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FName StartupLevelName = NAME_None;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FName MainMenuLevelName = NAME_None;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game")
    EHNLevel CurrentLevel = EHNLevel::Default;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
    FName UserName = "User";

    virtual void Init() override;
public:
    FORCEINLINE FName GetUserName() const { return UserName; }
    FORCEINLINE void SetUserName(const FName Name) { UserName = Name; }
    
    FName GetLevelName() const;
    FORCEINLINE EHNLevel GetLevel() const { return CurrentLevel; }
    FORCEINLINE void SetLevel(EHNLevel Level) { CurrentLevel = Level; }
    
    UFUNCTION()
    void SaveUserName(FName Name);
    UFUNCTION()
    void SaveScores(const FHNScoresData& ScoresData);

    UHNSaveGame* LoadGame() const;
    
private:
    void CreateSaveFile();
    void SaveGame(UHNSaveGame* SaveGame);

};