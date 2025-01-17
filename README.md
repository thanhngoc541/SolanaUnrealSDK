
# **SolanaSDK - Unreal Engine Plugin for Solana Blockchain Integration**

## **Overview**
The **SolanaSDK** project integrates the Solana blockchain into Unreal Engine, providing seamless blockchain-based functionalities such as:

- Wallet creation and management
- SOL transfers
- Token creation and management
- Retrieving token balances
- Direct interaction with Solana blockchain features

This project includes a custom plugin called `SolanaPlugin` to simplify blockchain operations within Unreal Engine.

---

## **Project Structure**

The project adheres to Unreal Engine's standard folder structure, with the addition of the `SolanaPlugin` under the `Plugins` directory.

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
│       │   ├── Private/         # Private C++ source files
│       │   │   ├── SolanaManager.cpp
│       │   │   └── Other implementation files
│       │   ├── Public/          # Public header files
│       │   │   ├── SolanaManager.h
│       │   │   └── Other public headers
│       │   ├── ThirdParty/      # External SDKs and dependencies
│       │   │   ├── solana_sdk.h          # Solana SDK header
│       │   │   ├── libsolana_c_sdk.dylib # Precompiled Solana SDK binary
│       │   │   └── Additional headers/libraries
│       │   └── SolanaPlugin.Build.cs
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

## **Running the Project**

Follow these steps to run the project:

### **Step 1: Open the Project**
1. Clone or download the repository to your local machine.
2. Open the project in Unreal Engine by double-clicking the `YourProject.uproject` file.

### **Step 2: Build the Project**
1. Ensure you have the required C++ development environment set up for Unreal Engine.
2. Click **File > Generate Visual Studio Project Files** (or equivalent for your platform).
3. Open the generated project in your IDE (e.g., Visual Studio, Xcode).
4. Build the project to ensure all dependencies and plugins compile successfully.

### **Step 3: Set Up Solana RPC Endpoint**
1. Obtain a Solana RPC endpoint from a provider like [QuickNode](https://www.quicknode.com) or [Alchemy](https://www.alchemy.com).
2. Update the RPC URL in the Blueprint or C++ code where the Solana client is initialized:
   ```cpp
   SolanaManager->ConnectToSolana(TEXT("https://your-solana-rpc-endpoint.com"));
   ```

### **Step 4: Test Blockchain Features**
1. Use the provided Blueprints or C++ functions to:
   - Create and manage wallets.
   - Transfer SOL or SPL tokens.
   - Fetch balances and token details.
2. Examples are available in the `Content` folder under `Plugins/SolanaPlugin/Content`.

### **Step 5: Play the Game**
1. Click the **Play** button in the Unreal Engine Editor to test the blockchain interactions in your game.

---

## **Installing SolanaPlugin in Another Project**

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
1. After restarting, navigate to the **Blueprint Editor**.
2. Look for Solana-related Blueprint nodes such as `CreateWallet`, `TransferSOL`, or `GetBalance`.

---

## **How to Use**

### **Wallet Management**
- **Create Wallet**: Use the `CreateWallet` Blueprint node or the corresponding C++ function.
- **Save/Load Wallets**: Save the wallet to a file or load an existing one using the provided nodes.

### **Send SOL**
- Use the `TransferSOL` Blueprint node to send SOL to another wallet.
- Input the recipient address and the amount (in lamports).

### **Retrieve Balances**
- Use the `GetBalance` node to fetch the balance of a wallet.

### **Token Management**
- **Create SPL Tokens**: Use the `CreateSPLToken` function to create new tokens.
- **Mint Tokens**: Mint SPL tokens to a wallet.
- **Fetch Token Balances**: Retrieve associated token balances.

---

## **Building the Plugin**

If you need to rebuild the plugin or add features:

1. Modify the source files in `Source/SolanaPlugin`.
2. Ensure platform-specific binaries (e.g., `.dylib`, `.dll`) are in the `ThirdParty` directory.
3. Rebuild the plugin using Unreal Engine's build tools.

---

## **Contributing**

Contributions are welcome! To contribute:

1. Fork this repository.
2. Create a new branch for your feature or bug fix:
   ```bash
   git checkout -b feature/your-feature
   ```
3. Commit your changes:
   ```bash
   git commit -m "Add new feature"
   ```
4. Push to your branch:
   ```bash
   git push origin feature/your-feature
   ```
5. Open a pull request with a detailed description of your changes.

---

## **License**

This project is licensed under the [MIT License](LICENSE).

---

## **Acknowledgments**
- [Solana](https://solana.com) for its blockchain technology.
- Unreal Engine community for development support.
- Open-source contributors for their libraries and tools.

