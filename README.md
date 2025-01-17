# **SolanaSDK - Unreal Engine Plugin for Solana Blockchain Integration**

## **Overview**
SolanaSDK is an Unreal Engine plugin designed to seamlessly integrate Solana blockchain functionality into Unreal projects. This plugin enables developers to interact with Solana's blockchain, including wallet management, SOL transfers, token operations, and more.

---

## **Features**
- **Wallet Management**: Create, load, and save Solana wallets.
- **Blockchain Interactions**:
  - Fetch wallet balances.
  - Transfer SOL and SPL tokens.
  - Request testnet airdrops.
- **Token Operations**:
  - Mint SPL tokens.
  - Fetch token information.
  - Manage associated token accounts.
- **Blueprint Integration**: Full support for Unreal Engine Blueprints to simplify blockchain interactions.
- **Cross-Platform**: Compatible with macOS and other platforms supported by Unreal Engine.

---

## **Getting Started**

### **Prerequisites**
- Unreal Engine 5.5.1
- A Solana RPC endpoint (e.g., from [QuickNode](https://www.quicknode.com) or [Alchemy](https://www.alchemy.com))
- Git for version control
- C++ development environment for Unreal Engine

---

### **Installation**

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/yourusername/SolanaSDK.git
   ```

2. **Move the Plugin**:
   Copy the `SolanaPlugin` folder into your Unreal project’s `Plugins/` directory:
   ```
   /YourUnrealProject/Plugins/SolanaPlugin/
   ```

3. **Enable the Plugin**:
   - Open your Unreal project.
   - Go to `Edit > Plugins`.
   - Search for "SolanaPlugin" and enable it.
   - Restart the Unreal Editor if prompted.

4. **Verify Integration**:
   - Check for a `SolanaManager` Blueprint class in the plugin.
   - Test basic operations like wallet creation and SOL transfers.

---

### **Folder Structure**
```
SolanaSDK/
├── Plugins/
│   └── SolanaPlugin/
│       ├── Content/          # Example assets and Blueprints
│       ├── Source/           # Plugin C++ source files
│       ├── ThirdParty/       # Solana SDK and dependencies
│       ├── Resources/        # Icon and metadata files
│       └── SolanaPlugin.uplugin
├── Config/
├── Content/
├── Saved/
└── YourProject.uproject
```

---

## **Usage**

### **Blueprint Examples**
- **Create Wallet**: Use the `CreateWallet` function to generate a new wallet.
- **Transfer SOL**: Call the `TransferSOL` Blueprint node to send SOL to another wallet.
- **Get Balance**: Use the `GetBalance` node to retrieve wallet balances.

### **C++ Integration**
Include the plugin header in your code:
```cpp
#include "SolanaManager.h"
```

---

## **Contributing**
We welcome contributions to improve SolanaSDK. To contribute:
1. Fork the repository.
2. Create a feature branch: `git checkout -b feature/new-feature`.
3. Commit your changes: `git commit -m "Add new feature"`.
4. Push to the branch: `git push origin feature/new-feature`.
5. Open a pull request.

---

## **Support**
If you encounter any issues or have questions, please open an issue in this repository or contact us via [email](mailto:support@solanasdk.com).

---

## **License**
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

## **Acknowledgments**
- [Solana](https://solana.com) for its blockchain technology.
- Unreal Engine community for development support.
- Open-source contributors for their libraries and tools.

---

Feel free to customize this README based on your specific project details and preferences!
