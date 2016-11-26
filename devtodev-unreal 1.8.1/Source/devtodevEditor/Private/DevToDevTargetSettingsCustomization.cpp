// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "DevToDevEditorPrivatePCH.h"
#include "DevToDevTargetSettingsCustomization.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "PropertyEditing.h"

#include "ObjectEditorUtils.h"
#include "IDocumentation.h"
#include "OutputDevice.h"


TSharedRef<IDetailCustomization> FDevToDevTargetSettingsCustomization::MakeInstance()
{
	return MakeShareable(new FDevToDevTargetSettingsCustomization);
}

void FDevToDevTargetSettingsCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailLayout)
{
	IDetailCategoryBuilder& IosCategory = DetailLayout.EditCategory(TEXT("IosSetup"), FText::GetEmpty(), ECategoryPriority::Variable);

}

#undef LOCTEXT_NAMESPACE