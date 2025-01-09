#include "SolanaManager.h"
#include "Misc/MessageDialog.h"
#include "Engine/Engine.h"
#include "solana_sdk.h"

// Constructor: Initialize Solana Client
USolanaManager::USolanaManager()
{
    SolanaClient = nullptr; // Initialize as null
    UE_LOG(LogTemp, Log, TEXT("USolanaManager constructed."));
}

// Destructor: Free the Solana client
USolanaManager::~USolanaManager()
{
    if (SolanaClient)
    {
        free_client(SolanaClient);
        SolanaClient = nullptr;
        UE_LOG(LogTemp, Log, TEXT("SolanaClient freed in USolanaManager destructor."));
    }
}

// Static function to create an instance of SolanaManager
USolanaManager *USolanaManager::CreateSolanaManager()
{
    USolanaManager *Manager = NewObject<USolanaManager>();
    if (Manager)
    {
        UE_LOG(LogTemp, Log, TEXT("USolanaManager instance created successfully."));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create USolanaManager instance."));
    }
    return Manager;
}

// Connect to Solana RPC
void USolanaManager::ConnectToSolana(const FString &RpcUrl)
{
    FTCHARToUTF8 UTF8Converter(*RpcUrl);
    const char *CUrl = UTF8Converter.Get();

    SolanaClient = new_sol_client(CUrl);

    if (SolanaClient)
    {
        UE_LOG(LogTemp, Log, TEXT("Connected to Solana RPC at: %s"), *RpcUrl);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to connect to Solana RPC at: %s"), *RpcUrl);
    }
}

// Create a new wallet
FSolanaKeyPair USolanaManager::CreateWallet()
{
    FSolanaKeyPair Wallet;

    SolKeyPair *KeyPair = new_keypair();
    if (KeyPair)
    {
        // Copy private key
        for (int i = 0; i < 64; i++)
        {
            Wallet.PrivateKey[i] = KeyPair->bytes[i];
        }

        // Copy public key
        for (int i = 0; i < 32; i++)
        {
            Wallet.PublicKey.Data[i] = KeyPair->pubkey.data[i];
        }

        UE_LOG(LogTemp, Log, TEXT("New Wallet Created:"));
        UE_LOG(LogTemp, Log, TEXT("Public Key: %s"), *FString::FromHexBlob(Wallet.PublicKey.Data.GetData(), 32));
        UE_LOG(LogTemp, Log, TEXT("Private Key: %s"), *FString::FromHexBlob(Wallet.PrivateKey.GetData(), 64));

        free_payer(KeyPair);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create a new wallet."));
    }

    return Wallet;
}

// Retrieve balance for a wallet
void USolanaManager::GetBalance(const FSolanaPublicKey &PublicKey, FString &Balance, FString &ErrorMessage)
{
    if (!SolanaClient)
    {
        ErrorMessage = TEXT("Solana client is not initialized. Call ConnectToSolana first.");
        UE_LOG(LogTemp, Error, TEXT("%s"), *ErrorMessage);
        return;
    }

    SolPublicKey SolPubKey;
    memcpy(SolPubKey.data, PublicKey.Data.GetData(), 32);

    uint64_t Bal = get_balance(SolanaClient, &SolPubKey);

    if (Bal == 0)
    {
        ErrorMessage = TEXT("Failed to retrieve balance. Ensure the public key is correct.");
        UE_LOG(LogTemp, Error, TEXT("%s"), *ErrorMessage);
    }
    else
    {
        Balance = FString::Printf(TEXT("%llu"), Bal);
        UE_LOG(LogTemp, Log, TEXT("Balance for public key: %s is %s"), *FString::FromHexBlob(PublicKey.Data.GetData(), 32), *Balance);
    }
}
