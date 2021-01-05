// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    
    //welcoming the player
    PrintLine(TEXT("Welcome to Bull Cows!"));
    PrintLine(TEXT("Guess the 5 letter word!"));
    PrintLine(TEXT("please type something and press enter!"));

    InitGame();//setup the game
    HiddenWord = TEXT("aegis"); //set HiddenWord
    //set Live
    //prompt player for guess
}


void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();
    
    // Show Lives Left   
    // check if string is Isogram the proceed else retype
    // check the right number of characters if right proceed else retype
    
    if (Input == HiddenWord){
        // if answer is right win
        PrintLine(TEXT("You win!")); 
        // Press enter to PlayAgain
    }else {
        PrintLine(TEXT("You lose !"));
        // remove Live
        // check if life is > 0
        // if yes GuessAgain
        // Show Lives Left
        // else show GameOver and HiddenWords
        // prompt to play again, Press enter to play again ?
        // Check User Input
        // PlayAgain Or Quit

    }
}