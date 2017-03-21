#include "DevToDevEditorPrivatePCH.h"

#include "DevToDevEditor.h"

#include "DevToDevTargetSettingsCustomization.h"

#include "ModuleInterface.h"
#include "ISettingsModule.h"
#include "ModuleManager.h"

#include "DevToDevProjectSettings.h"

#define LOCTEXT_NAMESPACE "DevToDevPlugin"

void FDevToDevEditor::StartupModule()
{
    // register settings detail panel customization
    FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
    PropertyModule.RegisterCustomClassLayout(
                                             UDevToDevProjectSettings::StaticClass()->GetFName(),
                                             FOnGetDetailCustomizationInstance::CreateStatic(&FDevToDevTargetSettingsCustomization::MakeInstance)
                                             );
    
    PropertyModule.NotifyCustomizationModuleChanged();
    
    ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");
    if( SettingsModule != nullptr )
    {
        SettingsModule->RegisterSettings(
                                         "Project", "Plugins", "DevToDev",
                                         LOCTEXT( "DevToDevSettingsName", "DevToDev" ),
                                         LOCTEXT( "DevToDevSettingsDescription", "DevToDev settings" ),
                                         GetMutableDefault< UDevToDevProjectSettings >() );
    }
}

void FDevToDevEditor::ShutdownModule()
{
    ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");
    if( SettingsModule != nullptr )
    {
        SettingsModule->UnregisterSettings( "Project", "Plugins", "DevToDev" );
    }
}

IMPLEMENT_MODULE(FDevToDevEditor, DevToDevEditor)