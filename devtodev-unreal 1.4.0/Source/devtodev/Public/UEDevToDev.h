// Copyright 2018-2020 devtodev. All Rights Reserved.

#pragma once

#include "DevToDevProvider.h"
#include "Interfaces/IAnalyticsProviderModule.h"

class IAnalyticsProvider;

DECLARE_MULTICAST_DELEGATE_OneParam(FDTDPushTokenRegisteredDelegate, FString);
DECLARE_MULTICAST_DELEGATE_OneParam(FDTDPushTokenRegisteredErrorDelegate, FString);
DECLARE_MULTICAST_DELEGATE_OneParam(FDTDPushNotificationReceivedDelegate, FString);
DECLARE_MULTICAST_DELEGATE_TwoParams(FDTDPushNotificationOpenedDelegate, FString, FString);

class FAnalyticsDevToDev : public IAnalyticsProviderModule {
  public:
    struct FDevToDevProjectSettings {
        FString AppKey;
        FString SecretKey;

        bool LogEnabled = false;
        bool EnablePushNotifications = false;
    };

    TSharedPtr<FAnalyticsProviderDevToDev> DevToDevProvider;

    virtual TSharedPtr<IAnalyticsProvider> CreateAnalyticsProvider(const FAnalyticsProviderConfigurationDelegate& GetConfigValue) const override;

    static FDTDPushTokenRegisteredDelegate PushTokenRegisteredDelegate;
    static FDTDPushNotificationOpenedDelegate PushNotificationOpenedDelegate;
    static FDTDPushTokenRegisteredErrorDelegate PushTokenRegisteredErrorDelegate;
    static FDTDPushNotificationReceivedDelegate PushNotificationReceivedDelegate;

    static FDevToDevProjectSettings LoadProjectSettings();

  private:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
