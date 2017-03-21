// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "IAnalyticsProviderModule.h"
#include "DevToDevProvider.h"

class IAnalyticsProvider;
class DTDPushImpl;

DECLARE_MULTICAST_DELEGATE_OneParam(FDTDRegisterSuccessDelegate, FString);
DECLARE_MULTICAST_DELEGATE_OneParam(FDTDRegisterErrorDelegate, FString);
DECLARE_MULTICAST_DELEGATE_OneParam(FDTDPushReceivedDelegate, FString);
DECLARE_MULTICAST_DELEGATE_TwoParams(FDTDPushOpenedDelegate, FString, FString);

/**
 * The public interface to this module
 */
class FAnalyticsDevToDev : public IAnalyticsProviderModule
{
public:
	/** Singleton for analytics */
	TSharedPtr<FAnalyticsProviderDevToDev> DevToDevProvider;

	/**
	 * IAnalyticsProviderModule interface.
	 * Creates the analytics provider given a configuration delegate.
	 * The keys required exactly match the field names in the Config object. 
	 */
	virtual TSharedPtr<IAnalyticsProvider> CreateAnalyticsProvider(const FAnalyticsProviderConfigurationDelegate& GetConfigValue) const override;

	static FDTDRegisterSuccessDelegate PushRegisterSuccess;
	
	static FDTDRegisterErrorDelegate PushRegisterError;
	
	static FDTDPushReceivedDelegate PushReceived;

	static FDTDPushOpenedDelegate PushOpened;
	
	struct FDevToDevProjectSettings
	{
		FString IosAppKey;
		FString IosSecretKey;
		bool LogEnabled = false;
		bool EnablePushNotifications = false;
	};

	static FDevToDevProjectSettings LoadProjectSettings();
private:
	DTDPushImpl *pImpl;
	
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

