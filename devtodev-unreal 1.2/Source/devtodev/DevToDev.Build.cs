using UnrealBuildTool;
using System.IO;
using System;

namespace UnrealBuildTool.Rules {
	public class DevToDev : ModuleRules {
        public DevToDev(ReadOnlyTargetRules Target) : base(Target) {
            PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
            var ModulePath = ModuleDirectory;

            switch (Target.Platform) {
                case UnrealTargetPlatform.IOS:
                    PublicAdditionalFrameworks.Add(
                        new UEBuildFramework(
                            "devtodev",
                            "../../ThirdParty/iOS/devtodev.embeddedframework.zip"
                        )
                    );
                    PublicFrameworks.AddRange(
                        new string[] {
                            "UIKit",
                            "Foundation",
                            "AdSupport",
                            "StoreKit",
                            "CoreGraphics",
                            "Security",
                            "SystemConfiguration",
                            "UserNotifications"
                        }
                    );

                    PublicAdditionalLibraries.AddRange(
                        new string[] {
                            "z",
                            "c++"
                    });
                    break;

                case UnrealTargetPlatform.Android:
                    PrivateDependencyModuleNames.Add("Launch");
                    PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private/Android"));
                    break;
                case UnrealTargetPlatform.Win64:
                case UnrealTargetPlatform.Win32:
                case UnrealTargetPlatform.Mac:
                case UnrealTargetPlatform.XboxOne:
                case UnrealTargetPlatform.PS4:
                case UnrealTargetPlatform.HTML5:
                case UnrealTargetPlatform.Linux:
                
                default:
                break;
                    // throw new NotImplementedException("This target platform is not supported for devtodev SDK: " + Target.Platform.ToString());
            }

            PublicDependencyModuleNames.AddRange(
                new string[] {
					"Core",
					"CoreUObject",
                    "Engine"
				}
            );

            PrivateIncludePaths.Add(Path.GetFullPath(Path.Combine(ModulePath, "Private")));
            PrivateIncludePaths.Add(Path.GetFullPath(Path.Combine(ModulePath, "Public")));
            PublicIncludePaths.Add(Path.GetFullPath(Path.Combine(ModulePath, "Public")));

            PrivateDependencyModuleNames.AddRange(
                new string[] {
                    "Analytics",
                    "AnalyticsBlueprintLibrary",
                    "Engine"
				}
            );

            PublicIncludePathModuleNames.AddRange(
                new string[] {
                    "Analytics",
                    "AnalyticsBlueprintLibrary",
                    "Engine"
                }
            );

            if (Target.Platform == UnrealTargetPlatform.Android) {
                AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(ModuleDirectory, "../DTDAnalytics_APL.xml"));
            }
        }
	}
}
