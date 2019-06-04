// Copyright 2018-2019 devtodev. All Rights Reserved.

#include "DTDAnalyticsBlueprintFunctionLibrary.h"

#include "DTDWrapper.h"
#include "PeopleLibrary.h"

#include <map>

using namespace std;
using namespace devtodev;

UDTDAnalyticsBlueprintFunctionLibrary::UDTDAnalyticsBlueprintFunctionLibrary(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
}

map<string, string> AttributesToMap(const TArray<FAnalyticsEventAttr>& Attributes) {
    map<string, string> attributes;

    for (int32 Index = 0; Index < Attributes.Num(); Index++) {
        attributes[TCHAR_TO_UTF8(*Attributes[Index].Name)] = TCHAR_TO_UTF8(*Attributes[Index].Value);
    }

    return attributes;
}

void UDTDAnalyticsBlueprintFunctionLibrary::SetTrackingAvailability(bool trackingAllowed) {
    DTDAnalytics::SetTrackingAvailability(trackingAllowed);
}

void UDTDAnalyticsBlueprintFunctionLibrary::TutorialCompleted(int32 step) {
    DTDAnalytics::TutorialCompleted(step);
}

void UDTDAnalyticsBlueprintFunctionLibrary::LevelUp(int32 level) {
    DTDAnalytics::LevelUp(level);
}

void UDTDAnalyticsBlueprintFunctionLibrary::LevelUpWithAttributes(int32 level, const TArray<FAnalyticsEventAttr>& Attributes) {
    map<string, int> resources;
    FString key;
    FString value;
    for (int32 Index = 0; Index < Attributes.Num(); Index++) {
        key = Attributes[Index].Name;
        value = Attributes[Index].Value;
        resources[TCHAR_TO_UTF8(*key)] = FCString::Atoi(*value);
    }

    DTDAnalytics::LevelUp(level, resources);
}

void UDTDAnalyticsBlueprintFunctionLibrary::SetCurrentLevel(int32 level) {
    DTDAnalytics::SetCurrentLevel(level);
}

void UDTDAnalyticsBlueprintFunctionLibrary::SocialNetworkConnect(const FString& socialName) {
    DTDAnalytics::SocialNetworkConnect(TCHAR_TO_UTF8(*socialName));
}

void UDTDAnalyticsBlueprintFunctionLibrary::SocialNetworkPost(const FString& socialName, const FString& reason) {
    DTDAnalytics::SocialNetworkPost(TCHAR_TO_UTF8(*socialName), TCHAR_TO_UTF8(*reason));
}

void UDTDAnalyticsBlueprintFunctionLibrary::ReplaceUserId(const FString& from, const FString& to) {
    DTDAnalytics::ReplaceUserId(TCHAR_TO_UTF8(*from), TCHAR_TO_UTF8(*to));
}

void UDTDAnalyticsBlueprintFunctionLibrary::RealPayment(const FString& transactionId, float inAppPrice, const FString& inAppName,
                                                        const FString& inAppCurrencyISOCode) {
    DTDAnalytics::RealPayment(TCHAR_TO_UTF8(*transactionId), inAppPrice, TCHAR_TO_UTF8(*inAppName), TCHAR_TO_UTF8(*inAppCurrencyISOCode));
}

void UDTDAnalyticsBlueprintFunctionLibrary::Referrer(const TArray<FAnalyticsEventAttr>& Attributes) {
    map<string, string> resources;
    for (int32 Index = 0; Index < Attributes.Num(); Index++) {
        resources[TCHAR_TO_UTF8(*Attributes[Index].Name)] = TCHAR_TO_UTF8(*Attributes[Index].Value);
    }
    DTDAnalytics::Referrer(resources);
}

void UDTDAnalyticsBlueprintFunctionLibrary::StartProgressionEvent(const FString& locationName, const TArray<FAnalyticsEventAttr>& Attributes) {
    map<string, string> attributesMap = AttributesToMap(Attributes);
    DTDAnalytics::StartProgressionEvent(TCHAR_TO_UTF8(*locationName), attributesMap);
}

void UDTDAnalyticsBlueprintFunctionLibrary::EndProgressionEvent(const FString& locationName, const TArray<FAnalyticsEventAttr>& Attributes,
                                                                const TArray<FAnalyticsEventAttr>& Earned, const TArray<FAnalyticsEventAttr>& Spent) {
    map<string, string> attributesMap = AttributesToMap(Attributes);
    map<string, string> earnedMap = AttributesToMap(Earned);
    map<string, string> spentMap = AttributesToMap(Spent);

    DTDAnalytics::EndProgressionEvent(TCHAR_TO_UTF8(*locationName), attributesMap, earnedMap, spentMap);
}