// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTestCPPLib.h"

TMap<FString, int32> UMyTestCPPLib::UserAttempts;
FString UMyTestCPPLib::Answer;

FString UMyTestCPPLib::GetMyFirstCPP(FString UserID, FString Msg)
{
    return FString::Printf(TEXT("%s CPP lib in BP"), *Msg);
}

FString UMyTestCPPLib::StartNewGame()
{
    UserAttempts.Empty();  // 모든 플레이어의 시도 횟수 초기화

    TArray<int32> digits;
    FString result;

    // 1~9 사이의 숫자 9개를 배열에 넣기
    for (int32 i = 1; i <= 9; ++i)
    {
        digits.Add(i);
    }

    // 난수 생성 (중복 없이 3자리 숫자 선택)
    for (int32 i = 0; i < 3; ++i)
    {
        // 랜덤 인덱스 생성
        int32 index = FMath::RandRange(0, digits.Num() - 1);

        // 선택된 숫자 결과 문자열에 추가
        result += FString::Printf(TEXT("%d"), digits[index]);

        // 배열에서 해당 숫자를 제거하여 중복되지 않도록 함
        digits.RemoveAt(index);
    }
    Answer = result;
    return Answer;
}

int32 UMyTestCPPLib::CheckStrike(const FString& guess, const FString& answer) 
{
    int32 strikes = 0;
    for (int32 i = 0; i < 3; ++i) 
    {
        if (guess[i] == answer[i])
        {
            strikes++;
        }
    }
    return strikes;
}

int32 UMyTestCPPLib::CheckBall(const FString& guess, const FString& answer) 
{
    int32 balls = 0;
    for (int32 i = 0; i < 3; ++i) 
    {
        int32 index = INDEX_NONE;
        if (answer.FindChar(guess[i], index) && answer[i] != guess[i])
        {
            balls++;
        }
    }
    return balls;
}

FString UMyTestCPPLib::ProcessGuess(FString UserID, const FString& userGuess)
{
    // 무승부 체크 (질문 횟수를 증가시킨 후에 체크해야 함)
    if (UserAttempts.Num() == 2)  // 두 명의 플레이어가 모두 기회를 다 썼을 때
    {
        bool AllPlayersOut = true;
        for (auto& PlayerAttempt : UserAttempts)
        {
            if (PlayerAttempt.Value < 3)  // 한 명이라도 기회를 남겼다면 무승부 아님
            {
                AllPlayersOut = false;
                break;
            }
        }

        if (AllPlayersOut)
        {
            StartNewGame();
            return FString::Printf(TEXT("Draw. Resetting game..."));
        }
    }


    // 새로운 유저 초기화
    if (!UserAttempts.Contains(UserID))
    {
        UserAttempts.Add(UserID, 0);  // 새로운 유저 초기화
    }

    // 질문 횟수 체크
    if (UserAttempts[UserID] >= 3)  // 이미 3번을 초과한 경우
    {
        return FString::Printf(TEXT("%s : Number of questions exceeded."), *UserID);
    }

    // 질문 횟수 증가
    UserAttempts[UserID]++;
    UE_LOG(LogTemp, Warning, TEXT("User %s has attempted %d times."), *UserID, UserAttempts[UserID]);

    if (!IsValidGuess(userGuess))
    {
        return FString::Printf(TEXT("%s : %s Is Invalid guess! (Attempt %d)"), *UserID, *userGuess, UserAttempts[UserID]);
    }

    // 스트라이크와 볼 계산
    int32 strikes = CheckStrike(userGuess, Answer);
    int32 balls = CheckBall(userGuess, Answer);

    if (strikes == 3)  // 정답을 맞춘 경우
    {
        StartNewGame();
        return FString::Printf(TEXT("%s : %s 3S0B Win"), *UserID, *userGuess);
    }
    else if (strikes == 0 && balls == 0)
    {
        return FString::Printf(TEXT("%s : %s OUT (Attempt %d)"), *UserID, *userGuess, UserAttempts[UserID]);
    }
    else  // S와 B 출력
    {
        return FString::Printf(TEXT("%s : %s %dS%dB (Attempt %d)"), *UserID, *userGuess, strikes, balls, UserAttempts[UserID]);
    }
}

bool UMyTestCPPLib::IsValidGuess(const FString& guess)
{
    if (guess.Len() != 3) return false;
    
    TArray<TCHAR> uniqueDigits;
    for (int32 i = 0; i < guess.Len(); ++i)
    {
        // 숫자가 1~9 사이인지 체크
        if (guess[i] < '1' || guess[i] > '9')return false;
        // 중복된 숫자가 있는지 체크
        if (uniqueDigits.Contains(guess[i])) return false;
        uniqueDigits.Add(guess[i]);
    }
    return true;
}