// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "DevToDevProjectSettings.generated.h"

UCLASS(Config=Engine, DefaultConfig)
class UDevToDevProjectSettings : public UObject
{
    GENERATED_UCLASS_BODY()
    
public:
    
    // Game Key
    UPROPERTY(Config, EditAnywhere, Category=IosSetup)
    FString IosAppKey;
    
    // Secret Key
    UPROPERTY(Config, EditAnywhere, Category=IosSetup)
	FString IosSecretKey;
    
    // Log Build
    UPROPERTY(Config, EditAnywhere, Category=Debug)
    bool LogEnabled = false;

    UPROPERTY(Config, EditAnywhere, Category=PushNotifications)
    bool EnablePushNotifications = false;
};