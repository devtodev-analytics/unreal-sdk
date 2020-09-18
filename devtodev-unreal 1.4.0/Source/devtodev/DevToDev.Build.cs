using System.IO;

namespace UnrealBuildTool.Rules
{
    public class DevToDev : ModuleRules
    {
        private string ModulePath
        {
            get
            {
                return ModuleDirectory;
            }
        }

        private string ThirdPartyPath
        {
            get
            {
                return Path.GetFullPath(Path.Combine(ModulePath, "../../ThirdParty/"));
            }
        }

        private string BinariesPath
        {
            get
            {
                return Path.GetFullPath(Path.Combine(ModulePath, "../../Binaries/"));
            }
        }

        private string LibraryPath
        {
            get
            {
                return Path.GetFullPath(Path.Combine(ThirdPartyPath, "Win/"));
            }
        }

        private string IncludePath
        {
            get
            {
                return Path.GetFullPath(Path.Combine(ThirdPartyPath, "Win/Headers"));
            }
        }

        private string UnrealProjectBinariesPath
        {
            get
            {
                return Path.Combine(ModuleDirectory, "../../../../Binaries");
            }
        }

        public DevToDev(ReadOnlyTargetRules Target) : base(Target)
        {
            PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
            var ModulePath = ModuleDirectory;

            if (Target.Platform == UnrealTargetPlatform.IOS)
            {
                PublicAdditionalFrameworks.Add(
                        new Framework(
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
            }
            else if (Target.Platform == UnrealTargetPlatform.Android)
            {
                PrivateDependencyModuleNames.Add("Launch");
                PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private/Platforms/Android"));
            }
            else
            {
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

            if (Target.Platform == UnrealTargetPlatform.Android)
            {
                AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(ModuleDirectory, "../DTDAnalytics_APL.xml"));
            }
        }

        private void CopyFile(string source, string dest)
        {
            System.Console.WriteLine("Copying {0} to {1}", source, dest);
            if (System.IO.File.Exists(dest))
            {
                System.IO.File.SetAttributes(dest, System.IO.File.GetAttributes(dest) & ~System.IO.FileAttributes.ReadOnly);
            }

            try
            {
                var targetDirectory = Path.GetDirectoryName(dest);
                System.IO.Directory.CreateDirectory(targetDirectory);
                System.IO.File.Copy(source, dest, true);
            }
            catch (System.Exception ex)
            {
                System.Console.WriteLine("Failed to copy file: {0}", ex.Message);
            }
        }
    }
}
