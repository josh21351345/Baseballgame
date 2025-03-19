// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyTestCPPLib.generated.h"

UCLASS()
class UMyTestCPPLib : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    
    static FString Answer;
    static TMap<FString, int32> UserAttempts;  // 사용자별 질문 횟수 저장

    UFUNCTION(BlueprintCallable, Category = "BaseballGame")
    static FString GetMyFirstCPP(FString UserID, FString Msg);

    UFUNCTION(BlueprintCallable, Category = "BaseballGame")
    static FString StartNewGame();

    UFUNCTION(BlueprintCallable, Category = "BaseballGame")
    static FString ProcessGuess(FString UserID, const FString& userGuess);


    static bool IsValidGuess(const FString& guess);
    static int32 CheckStrike(const FString& guess, const FString& answer);
    static int32 CheckBall(const FString& guess, const FString& answer);
};