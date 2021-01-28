// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"



void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    
    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/WordList.txt");
    FFileHelper::LoadFileToStringArray(Words, *WordListPath);
    
    Isograms = GetValidWords(Words); 

    //GetValidWords(Words);
    SetupGame();
}

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{
    ClearScreen();

    //if the game is over then clearScreen and SetupGame() the game
    if(bGameOver)
    {
        ClearScreen();
        SetupGame();
    }else{
    // checking PlayerGuess
        ProcessGuess(PlayerInput);
    }
}

void UBullCowCartridge::SetupGame()
{
    bGameOver = false;
    HiddenWord = Isograms[FMath::RandRange(0, GetValidWords(Words).Num() - 1)];
    Lives = HiddenWord.Len();
   // PrintLine(TEXT("The HiddenWord is %s"), *HiddenWord); // Debug Line
    // welcoming the player
    PrintLine(TEXT("Welcome to Bull Cows!"));
    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
    PrintLine(TEXT("You have %i live"), Lives);
    PrintLine(TEXT("please type something and press enter!"));     // prompt player for guess
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
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
        PrintLine(TEXT("Sorry"));
        PrintLine(TEXT("The hidden word is %i letter long"), HiddenWord.Len());
        CheckLife();
        return;
    }
    if(!IsIsogram(Guess))
    {
        PrintLine(TEXT("No repeating letters"));
    }

    FBullCowCount Score = GetBullCows(Guess);
    
    PrintLine(TEXT("You have %i Bulls and %i Cows"), Score.Bulls, Score.Cows);
    
    LoseLife();
    
}

TArray<FString> UBullCowCartridge::GetValidWords(TArray<FString>& WordList) const
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

bool UBullCowCartridge::IsIsogram(const FString& Word) const
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
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{
    FBullCowCount Count;
    
    for (int32 i =1; i < Guess.Len(); i++)
    {
        if(Guess[i] == HiddenWord[i])
        {
            Count.Bulls++;
            continue;
        }
        for( int32 HiddenI = 0; HiddenI  < HiddenWord.Len(); HiddenI++)
        {
            if(Guess[i] == HiddenWord[HiddenI])
            {
                Count.Cows++;
                break;
            }
        }
    }
    return Count;
}


void UBullCowCartridge::CheckLife()
{
    if(Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You have no live left"));
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
    if(Lives <= 0)
    {
        PrintLine(TEXT("You lose! \nPress enter to play again"));
        PrintLine(TEXT("The hidden word was %s"), *HiddenWord);
    }else
    {
        PrintLine(TEXT("You win! \nPress enter to play again"));
    }
    
}
