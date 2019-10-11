// Copyright 2018-2019 devtodev. All Rights Reserved.

#include "DevToDevTargetSettingsCustomization.h"

#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "PropertyEditing.h"

#include "IDocumentation.h"
#include "ObjectEditorUtils.h"
#include "OutputDevice.h"

TSharedRef<IDetailCustomization> FDevToDevTargetSettingsCustomization::MakeInstance() {
    return MakeShareable(new FDevToDevTargetSettingsCustomization);
}

void FDevToDevTargetSettingsCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailLayout) {
    IDetailCategoryBuilder& IosCategory = DetailLayout.EditCategory(TEXT("IOSSettings"), FText::GetEmpty(), ECategoryPriority::Variable);
    IDetailCategoryBuilder& AndroidCategory = DetailLayout.EditCategory(TEXT("AndroidSettings"), FText::GetEmpty(), ECategoryPriority::Variable);
}

#undef LOCTEXT_NAMESPACE
