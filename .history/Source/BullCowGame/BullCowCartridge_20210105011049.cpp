// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    
    //welcoming the player
    PrintLine(TEXT("Welcome to Bull Cows!"));
    PrintLine(TEXT("Guess the 5 letter word!"));
    PrintLine(TEXT("please type something and press enter!"));

    //setup the game
    HiddenWord = TEXT("aegis"); //set hiddenword
    //set live
    //prompt player for guess
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();
    
    //check if string is isogram
    //check the right number of characters 
    //check if life is > 0
    if (Input == HiddenWord){
        PrintLine(TEXT("You win!"));
    }else {
        PrintLine(TEXT("You lose !"));
        //remove Live
    }
    //check if life is > 0
    //if yes Again
    //else show GameOver
    //prompt to play again
    
    
    
    
}