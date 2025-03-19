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
    UserAttempts.Empty();  // ��� �÷��̾��� �õ� Ƚ�� �ʱ�ȭ

    TArray<int32> digits;
    FString result;

    // 1~9 ������ ���� 9���� �迭�� �ֱ�
    for (int32 i = 1; i <= 9; ++i)
    {
        digits.Add(i);
    }

    // ���� ���� (�ߺ� ���� 3�ڸ� ���� ����)
    for (int32 i = 0; i < 3; ++i)
    {
        // ���� �ε��� ����
        int32 index = FMath::RandRange(0, digits.Num() - 1);

        // ���õ� ���� ��� ���ڿ��� �߰�
        result += FString::Printf(TEXT("%d"), digits[index]);

        // �迭���� �ش� ���ڸ� �����Ͽ� �ߺ����� �ʵ��� ��
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
    // ���º� üũ (���� Ƚ���� ������Ų �Ŀ� üũ�ؾ� ��)
    if (UserAttempts.Num() == 2)  // �� ���� �÷��̾ ��� ��ȸ�� �� ���� ��
    {
        bool AllPlayersOut = true;
        for (auto& PlayerAttempt : UserAttempts)
        {
            if (PlayerAttempt.Value < 3)  // �� ���̶� ��ȸ�� ����ٸ� ���º� �ƴ�
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


    // ���ο� ���� �ʱ�ȭ
    if (!UserAttempts.Contains(UserID))
    {
        UserAttempts.Add(UserID, 0);  // ���ο� ���� �ʱ�ȭ
    }

    // ���� Ƚ�� üũ
    if (UserAttempts[UserID] >= 3)  // �̹� 3���� �ʰ��� ���
    {
        return FString::Printf(TEXT("%s : Number of questions exceeded."), *UserID);
    }

    // ���� Ƚ�� ����
    UserAttempts[UserID]++;
    UE_LOG(LogTemp, Warning, TEXT("User %s has attempted %d times."), *UserID, UserAttempts[UserID]);

    if (!IsValidGuess(userGuess))
    {
        return FString::Printf(TEXT("%s : %s Is Invalid guess! (Attempt %d)"), *UserID, *userGuess, UserAttempts[UserID]);
    }

    // ��Ʈ����ũ�� �� ���
    int32 strikes = CheckStrike(userGuess, Answer);
    int32 balls = CheckBall(userGuess, Answer);

    if (strikes == 3)  // ������ ���� ���
    {
        StartNewGame();
        return FString::Printf(TEXT("%s : %s 3S0B Win"), *UserID, *userGuess);
    }
    else if (strikes == 0 && balls == 0)
    {
        return FString::Printf(TEXT("%s : %s OUT (Attempt %d)"), *UserID, *userGuess, UserAttempts[UserID]);
    }
    else  // S�� B ���
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
        // ���ڰ� 1~9 �������� üũ
        if (guess[i] < '1' || guess[i] > '9')return false;
        // �ߺ��� ���ڰ� �ִ��� üũ
        if (uniqueDigits.Contains(guess[i])) return false;
        uniqueDigits.Add(guess[i]);
    }
    return true;
}