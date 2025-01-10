// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "solana_sdk.h"
#include "UObject/NoExportTypes.h"
#include "SolanaManager.generated.h"

// Struct for Solana Public Key
USTRUCT(BlueprintType)
struct FSolanaPublicKey
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Solana")
	TArray<uint8> Data; // 32-byte public key

	FSolanaPublicKey()
	{
		Data.SetNum(32); // Initialize to 32 bytes
	}
};

// Struct for Solana Key Pair
USTRUCT(BlueprintType)
struct FSolanaKeyPair
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Solana")
	TArray<uint8> PrivateKey; // 64-byte private key

	UPROPERTY(BlueprintReadOnly, Category = "Solana")
	FSolanaPublicKey PublicKey; // Associated public key

	FSolanaKeyPair()
	{
		PrivateKey.SetNum(64); // Initialize to 64 bytes
	}
};

// Manager for Solana Blockchain Interactions
UCLASS(Blueprintable)
class SOLANAPLUGIN_API USolanaManager : public UObject
{
	GENERATED_BODY()

public:
	USolanaManager();
	~USolanaManager();

	// Static function to create an instance of SolanaManager
	UFUNCTION(BlueprintCallable, Category = "Solana")
	static USolanaManager *CreateSolanaManager();

	// Connect to Solana RPC
	UFUNCTION(BlueprintCallable, Category = "Solana")
	void ConnectToSolana(const FString &RpcUrl);

	// Create a new wallet
	UFUNCTION(BlueprintCallable, Category = "Solana")
	FSolanaKeyPair CreateWallet();

	// Retrieve balance for a wallet
	UFUNCTION(BlueprintCallable, Category = "Solana")
	void GetBalance(const FSolanaPublicKey &PublicKey, FString &Balance, FString &ErrorMessage);

	// Display Solana Public Key
	UFUNCTION(BlueprintCallable, Category = "Solana")
	FString DisplayPublicKey(const FSolanaPublicKey &PublicKey);

	// Display Solana Key Pair
	UFUNCTION(BlueprintCallable, Category = "Solana")
	FString DisplayKeyPair(const FSolanaKeyPair &KeyPair);

	UFUNCTION(BlueprintCallable, Category = "Solana")
	void ShowPopup(const FString &Title, const FString &Message);

	// Get Wallet Address from Solana Key Pair
	UFUNCTION(BlueprintCallable, Category = "Solana")
	FString GetWalletAddress(const FSolanaKeyPair &KeyPair);

	// Create and save wallet to a file
	UFUNCTION(BlueprintCallable, Category = "Solana")
	FSolanaKeyPair CreateAndSaveWallet(const FString &FilePath, FString &ErrorMessage);

	// Load a wallet from a file
	UFUNCTION(BlueprintCallable, Category = "Solana")
	FSolanaKeyPair LoadWalletFromFile(const FString &FilePath, FString &ErrorMessage);

private:
	SolClient *SolanaClient; // Pointer to Solana client
};