#include "BullCowCartridge.h"
#include "C:\Users\elzbi\Documents\Unreal Projects\BullCowGame-starter-kit\Intermediate\ProjectFiles\WordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    SetupGame();
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else ProcessGuess(Input);
}

void UBullCowCartridge::SetupGame()
{
    HiddenWord = GetValidWord(Words);
   // HiddenWord = TEXT("cadek");
    Lives = HiddenWord.Len();
    bGameOver = false;

    //powitanie
    PrintLine(TEXT("Welcome. Guess a %i letter word."), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives."), Lives);
    PrintLine(TEXT("You will get Bull for each guessed letter or Cow if letter is in wrong place."));
    PrintLine(TEXT("Remember the word is isogram.\nPress enter to start."));
   // PrintLine(TEXT("HiddenWord: %s."), *HiddenWord);
}
FString UBullCowCartridge::GetValidWord(const TArray <FString>& Words) const
{
    int32 Num=FMath::RandRange(0, Words.Num() - 1);
    if (Words[Num].Len() >= 4 && Words[Num].Len() <= 8 && IsIsogram(Words[Num]))
        return Words[Num];
    else return GetValidWord(Words);
}
bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    for (int32 i = 0; i < Word.Len(); i++)
    {
        for (int32 j = (i + 1); j < Word.Len(); j++)
        {
            if (Word[i] == Word[j]) return false;
        }
    }
    return true;
}
void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Press enter to play again!"));
}
void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("Well done! You guessed the word: %s"), *HiddenWord);
        EndGame();
        return;
    }
    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("Wrong! The word is %i letters long."), HiddenWord.Len());
        return;
    }
    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("Wrong! No reapeting letters."));
        return;
    }
    Lives--;
    PrintLine(TEXT("You lost a life!"));
    if (Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You are out of lives! Game over."));
        PrintLine(TEXT("The word was %s."), *HiddenWord);
        EndGame();
        return;
    }
    else
    {
        //show bullsCows 
        GetBullsCowsCount(Guess);
        PrintLine(TEXT("You have %i lives remainig."), Lives);
    }
}
void UBullCowCartridge::GetBullsCowsCount(const FString& Word) const
{
    int32 Bulls = 0;
    int32 Cows = 0;
    FString Help = Word;

    for (int32 i = 0; i < Word.Len(); i++)
    {
        for (int32 j = 0; j < Word.Len(); j++)
        {
            if (Word[i] == HiddenWord[j] && i != j) Cows++;
            if (Word[i] == HiddenWord[j] && i == j) Bulls++;
        }
    }
    PrintLine(TEXT("You have %i Bulls and %i Cows."), Bulls, Cows);
    //extra feature
    if (Bulls > 0)
    {
        for (int32 i = 0; i < Word.Len(); i++) if (Help[i] != HiddenWord[i]) Help[i] = '*';
        PrintLine(TEXT("Clue: %s"),*Help);
    }
}
