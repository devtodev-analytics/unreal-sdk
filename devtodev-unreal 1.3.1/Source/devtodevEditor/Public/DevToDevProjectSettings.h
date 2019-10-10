// Copyright 2018-2019 devtodev. All Rights Reserved.

#pragma once

#include "DevToDevProjectSettings.generated.h"

UCLASS(Config = Engine, DefaultConfig)
class UDevToDevProjectSettings : public UObject {
    GENERATED_UCLASS_BODY()

  public:
    // iOS
    UPROPERTY(Config, EditAnywhere, Category = "iOS | Analytics")
    FString IOSAppKey;

    UPROPERTY(Config, EditAnywhere, Category = "iOS | Analytics")
    FString IOSSecretKey;

    // Android
    UPROPERTY(Config, EditAnywhere, Category = "Android | Analytics")
    FString AndroidAppKey;

    UPROPERTY(Config, EditAnywhere, Category = "Android | Analytics")
    FString AndroidSecretKey;

    // Log Build
    UPROPERTY(Config, EditAnywhere, Category = Debug)
    bool LogEnabled = false;
};