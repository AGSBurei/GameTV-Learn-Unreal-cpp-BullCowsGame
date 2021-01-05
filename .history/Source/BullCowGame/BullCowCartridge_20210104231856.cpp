// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine("Welcome to the game of life!");
    PrintLine("please type something and press");
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{

}