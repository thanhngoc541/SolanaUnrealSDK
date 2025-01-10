#include "SolanaManager.h"
#include "Misc/MessageDialog.h"
#include "Engine/Engine.h"
#include "solana_sdk.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"

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

FString USolanaManager::DisplayPublicKey(const FSolanaPublicKey &PublicKey)
{
    FString KeyHex = FString::FromHexBlob(PublicKey.Data.GetData(), 32);

    // Log to Output Log
    UE_LOG(LogTemp, Log, TEXT("Public Key: %s"), *KeyHex);

    // Display on-screen message
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Public Key: %s"), *KeyHex));
    }

    // Show popup
    FText Title = FText::FromString(TEXT("Public Key"));
    FText Message = FText::FromString(FString::Printf(TEXT("Public Key: %s"), *KeyHex));
    FMessageDialog::Open(EAppMsgType::Ok, Message, &Title);

    return KeyHex;
}

// Display Solana Key Pair
FString USolanaManager::DisplayKeyPair(const FSolanaKeyPair &KeyPair)
{
    FString PrivateKeyHex = FString::FromHexBlob(KeyPair.PrivateKey.GetData(), 64);
    FString PublicKeyHex = FString::FromHexBlob(KeyPair.PublicKey.Data.GetData(), 32);

    // Log to Output Log
    UE_LOG(LogTemp, Log, TEXT("Key Pair Details:"));
    UE_LOG(LogTemp, Log, TEXT("Private Key: %s"), *PrivateKeyHex);
    UE_LOG(LogTemp, Log, TEXT("Public Key: %s"), *PublicKeyHex);

    // Display on-screen messages
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Key Pair Details:"));
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Public Key: %s"), *PublicKeyHex));
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Private Key: %s"), *PrivateKeyHex));
    }

    // Show popup
    FText Title = FText::FromString(TEXT("Key Pair Details"));
    FText Message = FText::FromString(FString::Printf(TEXT("Public Key: %s\nPrivate Key: %s"), *PublicKeyHex, *PrivateKeyHex));
    FMessageDialog::Open(EAppMsgType::Ok, Message, &Title);

    return FString::Printf(TEXT("Public Key: %s\nPrivate Key: %s"), *PublicKeyHex, *PrivateKeyHex);
}

void USolanaManager::ShowPopup(const FString &Title, const FString &Message)
{
    FText TitleText = FText::FromString(Title);
    FText MessageText = FText::FromString(Message);

    // Display the message dialog
    FMessageDialog::Open(EAppMsgType::Ok, MessageText, &TitleText);

    UE_LOG(LogTemp, Log, TEXT("Popup displayed with title: %s, message: %s"), *Title, *Message);
}

FString USolanaManager::GetWalletAddress(const FSolanaKeyPair &KeyPair)
{
    // Convert FSolanaKeyPair to SolKeyPair
    SolKeyPair Wallet;
    memcpy(Wallet.bytes, KeyPair.PrivateKey.GetData(), 64);
    memcpy(Wallet.pubkey.data, KeyPair.PublicKey.Data.GetData(), 32);

    // Call get_wallet_address to retrieve the address
    char *CAddress = get_wallet_address(&Wallet);

    if (!CAddress)
    {
        FString ErrorMessage = TEXT("Failed to retrieve wallet address.");
        UE_LOG(LogTemp, Error, TEXT("%s"), *ErrorMessage);
        return ErrorMessage;
    }

    // Convert C string to FString
    FString Address = FString(UTF8_TO_TCHAR(CAddress));

    // Free the allocated memory for the address
    free(CAddress);

    // Log and display the wallet address
    UE_LOG(LogTemp, Log, TEXT("Wallet Address: %s"), *Address);

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("Wallet Address: %s"), *Address));
    }

    return Address;
}

FSolanaKeyPair USolanaManager::CreateAndSaveWallet(const FString &FilePath, FString &ErrorMessage)
{
    FSolanaKeyPair Wallet; // Initialize the wallet struct to return

    // Determine the file path
    FString FinalFilePath = FilePath.IsEmpty()
                                ? FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("Wallet.json")) // Default path
                                : FilePath;

    // Log the resolved file path
    UE_LOG(LogTemp, Log, TEXT("Saving wallet to: %s"), *FinalFilePath);

    // Convert FilePath to a C string
    FTCHARToUTF8 UTF8Converter(*FinalFilePath);
    const char *CFilePath = UTF8Converter.Get();

    // Call the Solana SDK function to create and save the wallet
    SolKeyPair *KeyPair = create_and_save_wallet(CFilePath);
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
        ErrorMessage = FString::Printf(TEXT("Failed to create and save wallet to: %s"), *FinalFilePath);
        UE_LOG(LogTemp, Error, TEXT("%s"), *ErrorMessage);
    }

    return Wallet;
}

FSolanaKeyPair USolanaManager::LoadWalletFromFile(const FString &FilePath, FString &ErrorMessage)
{
    FSolanaKeyPair Wallet; // Initialize the wallet struct to return

    // Determine the file path
    FString FinalFilePath = FilePath.IsEmpty()
                                ? FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("Wallet.json")) // Default path
                                : FilePath;

    // Check if the file exists
    if (!FPaths::FileExists(FinalFilePath))
    {
        ErrorMessage = FString::Printf(TEXT("Wallet file not found at: %s"), *FinalFilePath);
        UE_LOG(LogTemp, Error, TEXT("%s"), *ErrorMessage);
        return Wallet;
    }

    // Convert FilePath to a C string
    FTCHARToUTF8 UTF8Converter(*FinalFilePath);
    const char *CFilePath = UTF8Converter.Get();

    // Call the Solana SDK function to load the wallet
    SolKeyPair *KeyPair = load_wallet_from_file(CFilePath);
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

        UE_LOG(LogTemp, Log, TEXT("Wallet loaded successfully from: %s"), *FinalFilePath);
        UE_LOG(LogTemp, Log, TEXT("Public Key: %s"), *FString::FromHexBlob(Wallet.PublicKey.Data.GetData(), 32));
        UE_LOG(LogTemp, Log, TEXT("Private Key: %s"), *FString::FromHexBlob(Wallet.PrivateKey.GetData(), 64));

        free_payer(KeyPair); // Free the allocated memory for the SolKeyPair
    }
    else
    {
        ErrorMessage = FString::Printf(TEXT("Failed to load wallet from file: %s"), *FinalFilePath);
        UE_LOG(LogTemp, Error, TEXT("%s"), *ErrorMessage);
    }

    return Wallet;
}
