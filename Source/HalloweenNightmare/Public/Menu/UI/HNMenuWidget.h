// Halloween Nightmare. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HNMenuWidget.generated.h"

class UEditableText;
class UHNTextButtonWidget;

UCLASS()
class HALLOWEENNIGHTMARE_API UHNMenuWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UHNTextButtonWidget* NewGameTextButtonWidget;

    UPROPERTY(meta = (BindWidget))
    UHNTextButtonWidget* ScoresTextButtonWidget;

    UPROPERTY(meta = (BindWidget))
    UHNTextButtonWidget* QuitTextButtonWidget;

    UPROPERTY(meta = (BindWidget))
    UEditableText* UserNameEditableText;
    
    virtual void NativeOnInitialized() override;

private:
    TArray<UHNTextButtonWidget*> TextButtonWidgets;

    UFUNCTION()
    void OnNewGame();

    UFUNCTION()
    void OnShowScores();

    UFUNCTION()
    void OnQuitGame();

    UFUNCTION()
    void OnUsernameCommitted(const FText& Text, ETextCommit::Type CommitMethod);
    
    FText GetUserName() const;
};