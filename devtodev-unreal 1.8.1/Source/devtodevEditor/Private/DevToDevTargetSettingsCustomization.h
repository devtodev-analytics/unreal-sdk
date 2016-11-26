// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "EditorStyle.h"
#include "PropertyEditorModule.h"
#include "DevToDevProjectSettings.h"

class FDevToDevTargetSettingsCustomization : public IDetailCustomization
{
public:

	// Makes a new instance of this detail layout class for a specific detail view requesting it
	static TSharedRef<IDetailCustomization> MakeInstance();

	// IDetailCustomization interface
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;
	// End of IDetailCustomization interface

public:
	static FDevToDevTargetSettingsCustomization& getInstance()
	{
		static FDevToDevTargetSettingsCustomization instance;  // Guaranteed to be destroyed.
		// Instantiated on first use.
		return instance;
	}
};