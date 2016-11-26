// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Runtime/Analytics/Analytics/Public/Interfaces/IAnalyticsProviderModule.h"
#include "DevToDevProvider.h"

class IAnalyticsProvider;

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
	virtual TSharedPtr<IAnalyticsProvider> CreateAnalyticsProvider(const FAnalytics::FProviderConfigurationDelegate& GetConfigValue) const override;
	
	struct FDevToDevProjectSettings
	{
		FString IosAppKey;
		FString IosSecretKey;
		bool LogEnabled = false;
		bool EnablePushNotifications = false;
	};

	static FDevToDevProjectSettings LoadProjectSettings();
private:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

