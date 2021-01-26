// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWord.Txt"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/WordList.txt");
    FFileHelper::LoadFileToStringArray(Words, *WordListPath);

    //GetValidWords(Words);
    SetupGame();
    
    PrintLine(TEXT("The number of word is: %i."), Words.Num());
    PrintLine(TEXT("The number of possible words is: %i."), GetValidWords(Words).Num());
    PrintLine(TEXT("The HiddenWord is: %s."), *HiddenWord);
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();

    //if the game is over then clearScreen and SetupGame() the game
    if(bGameOver)
    {
        ClearScreen();
        SetupGame();
    }else{
    // checking PlayerGuess
        ProcessGuess(Input, Lives);
    }
}

void UBullCowCartridge::SetupGame()
{
    bGameOver = false;
    HiddenWord = TEXT("cakes");
    Lives = HiddenWord.Len();
    PrintLine(TEXT("The HiddenWord is %s"), *HiddenWord); // Debug Line
    // welcoming the player
    PrintLine(TEXT("Welcome to Bull Cows!"));
    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
    PrintLine(TEXT("You have %i live"), Lives);
    PrintLine(TEXT("please type something and press enter!"));     // prompt player for guess

    const TCHAR HW[] = TEXT("cakes");
    PrintLine(TEXT("Character 1 of the hiden word is: %c"),HW[0]); // print c
    PrintLine(TEXT("The 4th char of HW is %c"), HW[3]); // print e

}

void UBullCowCartridge::ProcessGuess(const FString Guess, int32 Counter)
{
    // Check if Guess is Right
    if (Guess == HiddenWord){
        PrintLine(TEXT("You win!"));
        EndGame();
        return;
    }
    // Check if Guess have the right lenght
    if(HiddenWord.Len() != Guess.Len())
    {
        LoseLife();
        CheckLife();
        PrintLine(TEXT("Sorry"));
        PrintLine(TEXT("The hidden word is %i letter long"), HiddenWord.Len());
        
        return;
    }
    if(!IsIsogram(Guess))
    {
        PrintLine(TEXT("No repeating letters"));
    }
    LoseLife();
}
TArray<FString> UBullCowCartridge::GetValidWords( TArray<FString> WordList) const
{
    TArray<FString> ValidWords;
    for (FString AWord : WordList)
    {
        if(AWord.Len() >= 4 && AWord.Len() <= 8 && IsIsogram(AWord))
        {
            ValidWords.Emplace(AWord);
        }
    }
    return ValidWords;
}

bool UBullCowCartridge::IsIsogram(FString Word) const
{
    for(int32 i = 0; i < Word.Len(); i++)
    {
        for(int32 Comparison = i + 1; Comparison < Word.Len(); Comparison++)
        {
            if(Word[i] == Word[Comparison])
            {
                return false;
            }
        }
    }
    return true;
    //for(int32 i = 0; i < Word.Len(); i++)
    //{
    //    PrintLine(TEXT("%c"),Word[i]);
       
    //}
    
}

void UBullCowCartridge::CheckLife()
{
    if(Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You have no live left"));
        PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);
        EndGame();
    }
}

void UBullCowCartridge::LoseLife()
{
    PrintLine(TEXT("You have lost a live, %i live left, Guess again."), --Lives);
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    ClearScreen();
    PrintLine(TEXT("\nPress enter to play again"));
}
