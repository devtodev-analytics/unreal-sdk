using UnrealBuildTool;
using System.IO;
using System;


namespace UnrealBuildTool.Rules
{
	public class DevToDev : ModuleRules
	{
        public DevToDev(TargetInfo Target)
		{
            var ModulePath = Path.GetDirectoryName(RulesCompiler.GetModuleFilename(this.GetType().Name));
            var DTDPath = Path.GetFullPath(Path.Combine(ModulePath, "..", "ThirdParty"));
            var libPath = Path.Combine(DTDPath, "lib");

            PublicIncludePaths.Add(Path.Combine(DTDPath, "include"));

            switch (Target.Platform)
            {
                case UnrealTargetPlatform.IOS:
                    PublicAdditionalLibraries.Add(Path.Combine(libPath, "ios", "libdevtodev.a"));
                    PublicFrameworks.AddRange(
                        new string[] {
                            "UIKit",
                            "Foundation",
                            "AdSupport",
                            "StoreKit",
                            "CoreGraphics",
                            "Security",
                            "SystemConfiguration"
                        }
                    );

                    PublicAdditionalLibraries.AddRange(
                        new string[] {
                            "z",
                            "c++"
                    });
                    break;

                case UnrealTargetPlatform.Android:
                case UnrealTargetPlatform.XboxOne:
                case UnrealTargetPlatform.PS4:
                case UnrealTargetPlatform.WinRT:
                case UnrealTargetPlatform.WinRT_ARM:
                case UnrealTargetPlatform.HTML5:
                case UnrealTargetPlatform.Linux:
                case UnrealTargetPlatform.Win64:
                case UnrealTargetPlatform.Win32:
                case UnrealTargetPlatform.Mac:
                default:
                break;
                    // throw new NotImplementedException("This target platform is not supported for devtodev SDK: " + Target.Platform.ToString());
            }

            PublicDependencyModuleNames.AddRange(
                new string[]
				{
					"Core",
					"CoreUObject",
                    "Engine"
				}
            );

            PrivateIncludePaths.Add(Path.GetFullPath(Path.Combine(ModulePath, "Private")));
            PrivateIncludePaths.Add(Path.GetFullPath(Path.Combine(ModulePath, "Public")));
            PublicIncludePaths.Add(Path.GetFullPath(Path.Combine(ModulePath, "Public")));


            PrivateDependencyModuleNames.AddRange(
                new string[]
				{
                    "Analytics",
                    "AnalyticsBlueprintLibrary"
				}
            );

            PublicIncludePathModuleNames.AddRange(
                new string[]
                {
                    "Analytics",
                    "AnalyticsBlueprintLibrary"
                }
            );
        }
	}
}