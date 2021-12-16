// Copyright 2018-2019 devtodev. All Rights Reserved.

#include "UEDevToDev.h"

#include "DTDWrapper.h"
#include "PeopleLibrary.h"

#include <map>
#include <string>

using namespace std;
using namespace devtodev;

#define DTD_VERSION "1.1"

IMPLEMENT_MODULE(FAnalyticsDevToDev, DevToDev)
DEFINE_LOG_CATEGORY_STATIC(LogDevToDevAnalytics, Log, All);

FDTDPushTokenRegisteredDelegate PushTokenRegisteredDelegate;
FDTDPushNotificationOpenedDelegate PushNotificationOpenedDelegate;
FDTDPushTokenRegisteredErrorDelegate PushTokenRegisteredErrorDelegate;
FDTDPushNotificationReceivedDelegate PushNotificationReceivedDelegate;

void FAnalyticsDevToDev::StartupModule() {
    DevToDevProvider = MakeShareable(new FAnalyticsProviderDevToDev());
}

void FAnalyticsDevToDev::ShutdownModule() {
    if (DevToDevProvider.IsValid()) {
        DevToDevProvider->EndSession();
    }
}

// Provider
FAnalyticsProviderDevToDev::FAnalyticsProviderDevToDev() : isInitialized(false) {
}

FAnalyticsProviderDevToDev::~FAnalyticsProviderDevToDev() {
}

FAnalyticsDevToDev::FDevToDevProjectSettings FAnalyticsDevToDev::LoadProjectSettings() {
    FDevToDevProjectSettings Settings;

    if (!GConfig)
        return Settings;
#if PLATFORM_IOS // TODO
    GConfig->GetString(TEXT("/Script/DevToDevEditor.DevToDevProjectSettings"), TEXT("IOSAppKey"), Settings.AppKey, GEngineIni);
    GConfig->GetString(TEXT("/Script/DevToDevEditor.DevToDevProjectSettings"), TEXT("IOSSecretKey"), Settings.SecretKey, GEngineIni);
#elif PLATFORM_ANDROID
    GConfig->GetString(TEXT("/Script/DevToDevEditor.DevToDevProjectSettings"), TEXT("AndroidAppKey"), Settings.AppKey, GEngineIni);
    GConfig->GetString(TEXT("/Script/DevToDevEditor.DevToDevProjectSettings"), TEXT("AndroidSecretKey"), Settings.SecretKey, GEngineIni);
#endif

    GConfig->GetBool(TEXT("/Script/DevToDevEditor.DevToDevProjectSettings"), TEXT("LogEnabled"), Settings.LogEnabled, GEngineIni);

    return Settings;
}

TSharedPtr<IAnalyticsProvider> FAnalyticsDevToDev::CreateAnalyticsProvider(const FAnalyticsProviderConfigurationDelegate& GetConfigValue) const {
    if (!DevToDevProvider->IsInitialized()) {
        FAnalyticsDevToDev::FDevToDevProjectSettings ProjectSettings = FAnalyticsDevToDev::LoadProjectSettings();

        DTDAnalytics::SetActiveLog(ProjectSettings.LogEnabled);
        DTDAnalytics::Initialize(TCHAR_TO_UTF8(*ProjectSettings.AppKey), TCHAR_TO_UTF8(*ProjectSettings.SecretKey));

        DevToDevProvider->SetInitialized(true);
    }

    return DevToDevProvider;
}

bool FAnalyticsProviderDevToDev::StartSession(const TArray<FAnalyticsEventAttribute>& Attributes) {
    UE_LOG(LogDevToDevAnalytics, Warning, TEXT("FAnalyticsProviderStartSession ignored."));
    return true;
}

void FAnalyticsProviderDevToDev::EndSession() {
    UE_LOG(LogDevToDevAnalytics, Warning, TEXT("FAnalyticsProviderEndSession ignored."));
}

void FAnalyticsProviderDevToDev::FlushEvents() {
    DTDAnalytics::SendBufferedEvents();
}

void FAnalyticsProviderDevToDev::SetUserID(const FString& InUserID) {
    DTDAnalytics::SetUserId(TCHAR_TO_UTF8(*InUserID));
}

FString FAnalyticsProviderDevToDev::GetUserID() const {
    return FString(DTDAnalytics::GetUserId());
}

FString FAnalyticsProviderDevToDev::GetSessionID() const {
    UE_LOG(LogDevToDevAnalytics, Warning, TEXT("FAnalyticsProviderGetSessionID ignored."));
    return TEXT("");
}

bool FAnalyticsProviderDevToDev::SetSessionID(const FString& InSessionID) {
    UE_LOG(LogDevToDevAnalytics, Warning, TEXT("FAnalyticsProviderSetSessionID ignored."));
    return false;
}

void FAnalyticsProviderDevToDev::RecordItemPurchase(const FString& ItemId, int ItemQuantity, const TArray<FAnalyticsEventAttribute>& Attributes) {
    const int32 AttrCount = Attributes.Num();
    if (AttrCount > 0) {
        FString purchaseType;
        int32 purchasePrice;
        int32 purchaseAmount = ItemQuantity;
        FString purchaseCurrency;

        for (auto Attr : Attributes) {
            if (Attr.AttrName == TEXT("purchaseType")) {
                purchaseType = Attr.AttrValueString;
            } else if (Attr.AttrName == TEXT("purchasePrice")) {
                purchasePrice = FCString::Atoi(*Attr.ToString());
            } else if (Attr.AttrName == TEXT("purchaseCurrency")) {
                purchaseCurrency = Attr.AttrValueString;
            } else if (Attr.AttrName == TEXT("purchaseAmount")) {
                purchaseAmount = FCString::Atoi(*Attr.ToString());
            }
        }
        DTDAnalytics::InAppPurchase(TCHAR_TO_UTF8(*ItemId), TCHAR_TO_UTF8(*purchaseType), purchaseAmount, purchasePrice, TCHAR_TO_UTF8(*purchaseCurrency));
    }
}

void FAnalyticsProviderDevToDev::RecordCurrencyGiven(const FString& GameCurrencyType, int GameCurrencyAmount,
                                                     const TArray<FAnalyticsEventAttribute>& Attributes) {
    const int32 AttrCount = Attributes.Num();
    if (AttrCount > 0) {
        DTDAccrualType accrualType = DTDEarned;

        for (auto Attr : Attributes) {
            if (Attr.AttrName == TEXT("accrualType")) {
                if (Attr.AttrValueString == TEXT("Purchased")) {
                    accrualType = DTDPurchased;
                }
            }
        }

        DTDAnalytics::CurrencyAccrual(GameCurrencyAmount, TCHAR_TO_UTF8(*GameCurrencyType), accrualType);
    }
}

void FAnalyticsProviderDevToDev::RecordEvent(const FString& EventName, const TArray<FAnalyticsEventAttribute>& Attributes) {
    const int32 AttrCount = Attributes.Num();
    if (EventName.Len() > 0) {
        if (AttrCount > 0) {
            std::map<std::string, std::string> params;
            for (auto Attr : Attributes) {
                params[TCHAR_TO_UTF8(*Attr.AttrName)] = TCHAR_TO_UTF8(*Attr.AttrValueString);
            }
            DTDAnalytics::CustomEvent(TCHAR_TO_UTF8(*EventName), params);
        } else {
            DTDAnalytics::CustomEvent(TCHAR_TO_UTF8(*EventName));
        }
    }
}

void FAnalyticsProviderDevToDev::SetAge(int InAge) {
    UPeopleLibrary::Age(InAge);
}

void FAnalyticsProviderDevToDev::SetGender(const FString& InGender) {
    UPeopleLibrary::Gender(InGender);
}

// Common methods

bool FAnalyticsProviderDevToDev::IsInitialized() {
    return isInitialized;
}

void FAnalyticsProviderDevToDev::SetInitialized(bool initialized) {
    isInitialized = initialized;
}
