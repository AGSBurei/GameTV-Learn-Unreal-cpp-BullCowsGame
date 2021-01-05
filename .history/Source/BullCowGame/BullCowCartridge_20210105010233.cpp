// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    
    PrintLine(TEXT("Welcome to Bull Cows!"));
    PrintLine(TEXT("Guess the 5 letter word!"));
    PrintLine(TEXT("please type something and press enter!"));

    HiddenWord = TEXT("aegis");
    //set live
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();
    
    if (Input == HiddenWord){
        PrintLine(TEXT("You win!"));
    }else {
        PrintLine(TEXT("You lose !"));
    }
    //remove live
    //check
}