// Halloween Nightmare. All Rights Reserved.


#include "Menu/UI/HNScoresWidget.h"

#include "HNCoreTypes.h"
#include "HNGameInstance.h"
#include "HNGameModeBase.h"
#include "HNSaveGame.h"
#include "Components/VerticalBox.h"
#include "UI/HNScoreRowWidget.h"

void UHNScoresWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (!GetWorld()) return;

    if (const auto GameMode = Cast<AHNGameModeBase>(GetWorld()->GetAuthGameMode()))
    {
        GameMode->OnGameStateChanged.AddUObject(this, &UHNScoresWidget::OnGameStateChanged);
    }
}

void UHNScoresWidget::OnGameStateChanged(EHNGameState State)
{
    if (State == EHNGameState::Scores)
    {
        UpdateScoresTable();
    }
}

void UHNScoresWidget::UpdateScoresTable()
{
    if (!GetWorld() || !ScoresBox || !ScoreRowWidgetClass) return;

    ScoresBox->ClearChildren();
    
    if (const auto GameInstance = GetWorld()->GetGameInstance<UHNGameInstance>())
    {
        if (const auto SaveGame = GameInstance->LoadGame())
        {
            GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green,
FString::Printf(TEXT("UpdateScoresTable")));
            
            auto ScoreDataArray = SaveGame->GetScoresDataArray();
            
            ScoreDataArray.Sort([](const FHNScoresData& A, const FHNScoresData& B)
                { return A.Score > B.Score; });

            int32 PlaceNumber = 1;
            
            for (const auto& [UserName, LevelName, Score, DateTime] :ScoreDataArray)
            {
                GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green,
                    FString::Printf(TEXT("Widget Add: %i"), PlaceNumber));
                
                const auto ScoreRowWidget = CreateWidget<UHNScoreRowWidget>(GetWorld(), ScoreRowWidgetClass);
                
                ScoreRowWidget->SetPlace(FText::FromString(FString::FromInt(PlaceNumber)));
                ScoreRowWidget->SetUserName(FText::FromName(UserName));
                ScoreRowWidget->SetScore(FText::FromString(FString::FromInt(Score)));
                ScoreRowWidget->SetLevelName(FText::FromName(LevelName));
                ScoreRowWidget->SetDateTime(FText::FromString(DateTime.ToFormattedString(TEXT("%Y.%m.%d. %H:%M:%S"))));

                ScoresBox->AddChild(ScoreRowWidget);
                
                ++PlaceNumber;

                if (PlaceNumber >= ScoreTableRowsNum) break;
            }
        }
    }
}