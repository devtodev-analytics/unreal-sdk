// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

class FAnalyticsProviderDevToDev : public IAnalyticsProvider
{
private:
	bool isInitialized;
	
public:
	FAnalyticsProviderDevToDev();
	virtual ~FAnalyticsProviderDevToDev();

	// Analytics Provider
	virtual bool StartSession(const TArray<FAnalyticsEventAttribute>& Attributes) override;

	virtual void EndSession() override;
	void FlushEvents() override;

	virtual void SetUserID(const FString& InUserID) override;
	virtual FString GetUserID() const override;

	virtual FString GetSessionID() const override;
	virtual bool SetSessionID(const FString& InSessionID) override;

	virtual void RecordItemPurchase(const FString& ItemId, int ItemQuantity, const TArray<FAnalyticsEventAttribute>& EventAttrs) ;
	virtual void RecordCurrencyGiven(const FString& GameCurrencyType, int GameCurrencyAmount, const TArray<FAnalyticsEventAttribute>& EventAttrs) ;
	virtual void RecordEvent(const FString& EventName, const TArray<FAnalyticsEventAttribute>& Attributes) override;
	
	virtual void SetGender(const FString& InGender) ;

	virtual void SetAge(const int32 InAge) ;

	// Common
	bool IsInitialized();

	void SetInitialized(bool initialized);
};
