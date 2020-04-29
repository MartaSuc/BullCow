#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;
	void SetupGame();
	void EndGame();
	void ProcessGuess(const FString& Guess);
	FString GetValidWord(const TArray <FString>& Words) const;
	bool IsIsogram(const FString& Word) const;
	void GetBullsCowsCount(const FString& Word) const;

private:
	FString HiddenWord;
	bool bGameOver;
	int32 Lives;
};
