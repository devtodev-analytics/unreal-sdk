// Copyright 2018-2019 devtodev. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DevToDevProjectSettings.h"
#include "IDetailCustomization.h"
#include "PropertyEditorModule.h"

class FDevToDevTargetSettingsCustomization : public IDetailCustomization {
  public:
    static TSharedRef<IDetailCustomization> MakeInstance();

    virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;

  public:
    static FDevToDevTargetSettingsCustomization& getInstance() {
        static FDevToDevTargetSettingsCustomization instance;
        return instance;
    }
};