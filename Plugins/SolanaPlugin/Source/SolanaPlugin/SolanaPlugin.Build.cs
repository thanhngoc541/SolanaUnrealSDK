// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;
public class SolanaPlugin : ModuleRules
{
	public SolanaPlugin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(
			new string[] {
				Path.Combine(ModuleDirectory, "Public"),
				Path.Combine(ModuleDirectory, "ThirdParty"), // Include path for Solana SDK headers
			}
			);


		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);


		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);


		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...
			}
			);


		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
		string PluginPath = Path.Combine(ModuleDirectory, "ThirdParty/");
		string LibPath = Path.Combine(PluginPath, "libsolana_c_sdk.dylib");

		// Ensure the library exists to avoid build errors
		if (File.Exists(LibPath))
		{
			PublicAdditionalLibraries.Add(LibPath);
			RuntimeDependencies.Add(LibPath);
			System.Console.WriteLine("Warning: libsolana_rust_ffi.dylib founded at " + LibPath);
		}
		else
		{
			System.Console.WriteLine("Warning: libsolana_rust_ffi.dylib not found at " + LibPath);
		}
	}
}
