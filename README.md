# **SolanaSDK Unreal Engine Project**

### **Overview**
The **SolanaSDK** project integrates the Solana blockchain into Unreal Engine, enabling blockchain-based functionalities such as:

- Wallet creation and management
- SOL transfers
- Token creation and management
- Retrieving token balances
- Direct interaction with Solana blockchain features

This project is built with Unreal Engine and includes a custom plugin called `SolanaPlugin`.

---

## **Project Structure**

The project follows Unreal Engine's standard folder structure with the addition of the `SolanaPlugin` under the `Plugins` directory.

### **Folder Structure**

```
SolanaSDK/
├── Config/                      # Configuration files for the project
├── Content/                     # Game assets such as Blueprints, UI, and media
├── Plugins/
│   └── SolanaPlugin/
│       ├── Content/             # Example assets and Blueprints for the plugin
│       ├── Resources/           # Icon and metadata files for the plugin
│       ├── Source/              # Plugin source files
│       │   └── SolanaPlugin/
│       │       ├── Private/     # Private C++ source files
│       │       │   ├── SolanaManager.cpp
│       │       │   └── Other implementation files
│       │       ├── Public/      # Public header files
│       │       │   ├── SolanaManager.h
│       │       │   └── Other public headers
│       │       ├── ThirdParty/  # External SDKs and dependencies
│       │       │   ├── solana_sdk.h          # Solana SDK header
│       │       │   ├── libsolana_c_sdk.dylib # Precompiled Solana SDK binary
│       │       │   └── Additional headers/libraries
│       │       └── SolanaPlugin.Build.cs
│       └── SolanaPlugin.uplugin # Plugin descriptor file
├── Saved/                       # Auto-saved files
└── YourProject.uproject         # Unreal Engine project descriptor
```

---

## **SolanaPlugin**

The `SolanaPlugin` is a custom Unreal Engine plugin designed to interact with the Solana blockchain. It provides:

### **Key Features**
- **Wallet Management**: Create, load, and save wallets.
- **SOL Transfers**: Send SOL to other wallets.
- **Token Management**: Create SPL tokens and manage associated token accounts.
- **Token Balances**: Retrieve balances for SOL and SPL tokens.
- **Blueprint Integration**: Easy-to-use Blueprint nodes for blockchain operations.

---

## **Guide: Installing SolanaPlugin into Another Project**

You can easily install the `SolanaPlugin` in any Unreal Engine project by following these steps:

### **Step 1: Locate the Plugin**
1. Navigate to the `Plugins/SolanaPlugin` directory in this project.

### **Step 2: Copy the Plugin**
1. Copy the entire `SolanaPlugin` folder (including `Source`, `Content`, and `Resources`).

### **Step 3: Paste into Target Project**
1. Paste the `SolanaPlugin` folder into the `Plugins` folder of your target Unreal Engine project. 
   - If the `Plugins` folder doesn’t exist, create it in the root of your target project directory.

### **Step 4: Enable the Plugin**
1. Open your target project in Unreal Engine.
2. Go to **Edit > Plugins**.
3. Search for `SolanaPlugin` in the list of installed plugins.
4. Enable the plugin and restart the project if prompted.

### **Step 5: Verify Installation**
1. After restarting, you can verify the plugin by navigating to the **Blueprint Editor**.
2. Look for Solana-related Blueprint nodes like `CreateWallet`, `TransferSOL`, or `GetBalance`.

---

## **How to Use**

### **Wallet Management**
- Create a wallet using the `CreateWallet` Blueprint node or the corresponding C++ function.
- Save the wallet to a file or load an existing one.

### **Send SOL**
- Use the `TransferSOL` Blueprint node to send SOL to another wallet.
- Input the recipient address and the amount in lamports.

### **Retrieve Balances**
- Use the `GetBalance` node to fetch the balance of a wallet.

### **Token Management**
- Create SPL tokens using the `CreateSPLToken` function.
- Mint tokens or fetch associated token balances.

---

## **Building the Plugin**

If you need to rebuild the plugin or add features:

1. Modify the source files in `Source/SolanaPlugin`.
2. Ensure platform-specific binaries (e.g., `.dylib`, `.dll`) are in the `ThirdParty` directory.
3. Rebuild the plugin using Unreal Engine's build tools.

---

## **Contributing**

Contributions are welcome! If you’d like to contribute:
1. Fork this repository.
2. Create a new branch for your feature or bug fix.
3. Submit a pull request with a detailed description of your changes.

---

## **License**

This project is licensed under the [MIT License](LICENSE).

--- 

Feel free to modify this README further to include any project-specific details!
