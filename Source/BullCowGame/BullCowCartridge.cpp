// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"


void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    SetupGame();
}


void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();

    //if the game is over then clearScreen and SetupGame() the game
    if(bGameOver)
    {
        SetupGame();
    }else{
    // checking PlayerGuess
        ProcessGuess(Input, Lives);
    }
}


void UBullCowCartridge::SetupGame()
{
    bGameOver = false;
    HiddenWord = TEXT("aegis");
    Lives = HiddenWord.Len();
    PrintLine(TEXT("The HiddenWord is %s"), *HiddenWord); //Debug Line
    //welcoming the player
    PrintLine(TEXT("Welcome to Bull Cows!"));
    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
    PrintLine(TEXT("You have %i live"), Lives);
    PrintLine(TEXT("please type something and press enter!"));     //prompt player for guess    
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
        PrintLine(TEXT("Sorry, try again ! "));
        PrintLine(TEXT("The hidden word is %i letter long"), HiddenWord.Len());
        
        return;
    }
    //if(IsIsogram)
    //{
    //    PrintLine(TEXT("No repeating letters, guess again"));
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
    PrintLine(TEXT("You have lost a live, %i live left"), --Lives);
}
void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    ClearScreen();
    PrintLine(TEXT("\nPress enter to play again"));
}