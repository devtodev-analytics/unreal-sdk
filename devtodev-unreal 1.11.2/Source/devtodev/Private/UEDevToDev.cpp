#include "DevToDevPrivatePCH.h"
#include "DevToDev.h"
#include "UEDevToDev.h"
#include "PeopleLibrary.h"
#include "DevToDevPushiOS.h"

#include <map>
#include <string>

#define DTD_VERSION "1.0"

DEFINE_LOG_CATEGORY_STATIC(LogDevToDevAnalytics, Log, All);

IMPLEMENT_MODULE( FAnalyticsDevToDev, DevToDev )

FDTDRegisterSuccessDelegate FAnalyticsDevToDev::PushRegisterSuccess;

FDTDRegisterErrorDelegate FAnalyticsDevToDev::PushRegisterError;

FDTDPushReceivedDelegate FAnalyticsDevToDev::PushReceived;

FDTDPushOpenedDelegate FAnalyticsDevToDev::PushOpened;

void FAnalyticsDevToDev::StartupModule()
{
	UE_LOG(LogDevToDevAnalytics, Display, TEXT("FAnalyticsDevToDev Constructor"));
	DevToDevProvider = MakeShareable(new FAnalyticsProviderDevToDev());

	#if PLATFORM_IOS
		pImpl = new DevToDevPushiOS();
	#else 
		pImpl = new DTDPushImpl();
	#endif
}

void FAnalyticsDevToDev::ShutdownModule()
{
	if (DevToDevProvider.IsValid())
	{
		DevToDevProvider->EndSession();
	}

	delete pImpl;
}

// Provider
FAnalyticsProviderDevToDev::FAnalyticsProviderDevToDev() : isInitialized(false)
{

}

FAnalyticsProviderDevToDev::~FAnalyticsProviderDevToDev()
{

}

FAnalyticsDevToDev::FDevToDevProjectSettings FAnalyticsDevToDev::LoadProjectSettings()
{
	FDevToDevProjectSettings Settings;

	if (!GConfig) return Settings;

	GConfig->GetString(TEXT("/Script/DevToDevEditor.DevToDevProjectSettings"), TEXT("IosAppKey"), Settings.IosAppKey, GEngineIni);
	GConfig->GetString(TEXT("/Script/DevToDevEditor.DevToDevProjectSettings"), TEXT("IosSecretKey"), Settings.IosSecretKey, GEngineIni);
	GConfig->GetBool(TEXT("/Script/DevToDevEditor.DevToDevProjectSettings"), TEXT("LogEnabled"), Settings.LogEnabled, GEngineIni);
	GConfig->GetBool(TEXT("/Script/DevToDevEditor.DevToDevProjectSettings"), TEXT("EnablePushNotifications"), Settings.EnablePushNotifications, GEngineIni);

	return Settings;
}

TSharedPtr<IAnalyticsProvider> FAnalyticsDevToDev::CreateAnalyticsProvider(const FAnalyticsProviderConfigurationDelegate& GetConfigValue) const
{		
	if (!DevToDevProvider->IsInitialized()) 
	{
		FAnalyticsDevToDev::FDevToDevProjectSettings ProjectSettings = FAnalyticsDevToDev::LoadProjectSettings();

		////// Enable log
		devtodev::DevToDev::SetActiveLog(ProjectSettings.LogEnabled);
		////// Initialize
		devtodev::DevToDev::Initialize(TCHAR_TO_UTF8(*ProjectSettings.IosAppKey), TCHAR_TO_UTF8(*ProjectSettings.IosSecretKey));
		pImpl->Initialize();
		DevToDevProvider->SetInitialized(true);
	}

	return DevToDevProvider;
}

bool FAnalyticsProviderDevToDev::StartSession(const TArray<FAnalyticsEventAttribute>& Attributes)
{	
	UE_LOG(LogDevToDevAnalytics, Warning, TEXT("FAnalyticsProviderDevToDev::StartSession ignored."));
	return true;
}

void FAnalyticsProviderDevToDev::EndSession()
{
	UE_LOG(LogDevToDevAnalytics, Warning, TEXT("FAnalyticsProviderDevToDev::EndSession ignored."));
}

void FAnalyticsProviderDevToDev::FlushEvents()
{
	devtodev::DevToDev::SendBufferedEvents();
}

void FAnalyticsProviderDevToDev::SetUserID(const FString& InUserID)
{
	devtodev::DevToDev::SetUserId(TCHAR_TO_UTF8(*InUserID));
}

FString FAnalyticsProviderDevToDev::GetUserID() const
{
	return FString(devtodev::DevToDev::GetUserId());
}

FString FAnalyticsProviderDevToDev::GetSessionID() const
{
	UE_LOG(LogDevToDevAnalytics, Warning, TEXT("FAnalyticsProviderDevToDev::GetSessionID ignored."));
	return TEXT("");
}

bool FAnalyticsProviderDevToDev::SetSessionID(const FString& InSessionID)
{
	UE_LOG(LogDevToDevAnalytics, Warning, TEXT("FAnalyticsProviderDevToDev::SetSessionID ignored."));
	return false;
}

void FAnalyticsProviderDevToDev::RecordItemPurchase(const FString& ItemId, int ItemQuantity, const TArray<FAnalyticsEventAttribute>& Attributes)
{
	const int32 AttrCount = Attributes.Num();
	if (AttrCount > 0) {
		FString purchaseType;
		int32 purchasePrice;
		FString purchaseCurrency;

		for (auto Attr : Attributes) {
			if (Attr.AttrName == TEXT("purchaseType")) {
				purchaseType = Attr.AttrValue;
			} else if (Attr.AttrName == TEXT("purchasePrice")) {
				purchasePrice = FCString::Atoi(*Attr.AttrValue);
			} else if (Attr.AttrName == TEXT("purchaseCurrency")) {
				purchaseCurrency = Attr.AttrValue;
			}
		}

		devtodev::DevToDev::InAppPurchase(TCHAR_TO_UTF8(*ItemId), TCHAR_TO_UTF8(*purchaseType), ItemQuantity, purchasePrice, TCHAR_TO_UTF8(*purchaseCurrency));
	}
}

void FAnalyticsProviderDevToDev::RecordCurrencyGiven(const FString& GameCurrencyType, int GameCurrencyAmount, const TArray<FAnalyticsEventAttribute>& Attributes)
{
	const int32 AttrCount = Attributes.Num();
	if (AttrCount > 0) {
		devtodev::DTDAccrualType accrualType = devtodev::DTDEarned;

		for (auto Attr : Attributes) {
			if (Attr.AttrName == TEXT("accrualType"))
			{
				if (Attr.AttrValue == TEXT("Purchased")) {
					accrualType = devtodev::DTDPurchased;
				}
			}
		}

		devtodev::DevToDev::CurrencyAccrual(GameCurrencyAmount, TCHAR_TO_UTF8(*GameCurrencyType), accrualType);
	}
}

void FAnalyticsProviderDevToDev::RecordEvent(const FString& EventName, const TArray<FAnalyticsEventAttribute>& Attributes)
{
	const int32 AttrCount = Attributes.Num();
	if (EventName.Len() > 0)
    {
        if (AttrCount > 0) {
        	std::map<std::string, std::string> params;
        	for (auto Attr : Attributes) {
        		params[TCHAR_TO_UTF8(*Attr.AttrName)] = TCHAR_TO_UTF8(*Attr.AttrValue);
        	}
        	devtodev::DevToDev::CustomEvent(TCHAR_TO_UTF8(*EventName), params);
        } else {
        	devtodev::DevToDev::CustomEvent(TCHAR_TO_UTF8(*EventName));
        }
    }
    
    UE_LOG(LogDevToDevAnalytics, Display, TEXT("DevToDev::RecordEvent('%s', %d attributes)"), *EventName, AttrCount);
}

void FAnalyticsProviderDevToDev::SetAge(int InAge)
{
    UPeopleLibrary::Age(InAge);
}

void FAnalyticsProviderDevToDev::SetGender(const FString& InGender)
{
    UPeopleLibrary::Gender(InGender);
}

// Common methods

bool FAnalyticsProviderDevToDev::IsInitialized()
{
	return isInitialized;
}

void FAnalyticsProviderDevToDev::SetInitialized(bool initialized) 
{
	isInitialized = initialized;
}
