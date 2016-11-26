#include "DevToDevPrivatePCH.h"
#include "DevToDevBlueprintFunctionLibrary.h"
#include "DevToDev.h"
#include "PeopleLibrary.h"

#include <map>

std::map<std::string, std::string> AttributesToMap(const TArray<FAnalyticsEventAttr>& Attributes)
{
	std::map<std::string, std::string> attributes;

	for (int32 Index = 0; Index < Attributes.Num(); Index++)
    {
        attributes[TCHAR_TO_UTF8(*Attributes[Index].Name)] = TCHAR_TO_UTF8(*Attributes[Index].Value);
    }

	return attributes;
}

void UDevToDevBlueprintFunctionLibrary::TutorialCompleted(int32 step) 
{
	devtodev::DevToDev::TutorialCompleted(step);
}

void UDevToDevBlueprintFunctionLibrary::LevelUp(int32 level)
{
	devtodev::DevToDev::LevelUp(level);
}

void UDevToDevBlueprintFunctionLibrary::LevelUpWithAttributes(int32 level, const TArray<FAnalyticsEventAttr>& Attributes)
{
	std::map<std::string, int> resources;
	FString key;
	FString value;
	for (int32 Index = 0; Index < Attributes.Num(); Index++)
	{
		key = Attributes[Index].Name;
		value = Attributes[Index].Value;
		resources[TCHAR_TO_UTF8(*key)] = FCString::Atoi(*value);
	}

	devtodev::DevToDev::LevelUp(level, resources);
}

void UDevToDevBlueprintFunctionLibrary::SetCurrentLevel(int32 level)
{
	devtodev::DevToDev::SetCurrentLevel(level);
}

void UDevToDevBlueprintFunctionLibrary::SocialNetworkConnect(const FString& socialName)
{
	devtodev::DevToDev::SocialNetworkConnect(TCHAR_TO_UTF8(*socialName));
}

void UDevToDevBlueprintFunctionLibrary::SocialNetworkPost(const FString& socialName, const FString& reason)
{
	devtodev::DevToDev::SocialNetworkPost(TCHAR_TO_UTF8(*socialName), TCHAR_TO_UTF8(*reason));
}

void UDevToDevBlueprintFunctionLibrary::ReplaceUserId(const FString& from, const FString& to)
{
	devtodev::DevToDev::ReplaceUserId(TCHAR_TO_UTF8(*from), TCHAR_TO_UTF8(*to));
}

void UDevToDevBlueprintFunctionLibrary::RealPayment(const FString& transactionId, float inAppPrice, const FString& inAppName, const FString& inAppCurrencyISOCode)
{
	devtodev::DevToDev::RealPayment(TCHAR_TO_UTF8(*transactionId), inAppPrice, TCHAR_TO_UTF8(*inAppName), TCHAR_TO_UTF8(*inAppCurrencyISOCode));
}

void UDevToDevBlueprintFunctionLibrary::Referrer(const TArray<FAnalyticsEventAttr>& Attributes)
{
    std::map<std::string, std::string> resources;
    for (int32 Index = 0; Index < Attributes.Num(); Index++)
    {
        resources[TCHAR_TO_UTF8(*Attributes[Index].Name)] = TCHAR_TO_UTF8(*Attributes[Index].Value);
    }
    devtodev::DevToDev::Referrer(resources);
}

void UDevToDevBlueprintFunctionLibrary::StartProgressionEvent(const FString& locationName, const TArray<FAnalyticsEventAttr>& Attributes)
{
	std::map<std::string, std::string> attributesMap = AttributesToMap(Attributes);
    devtodev::DevToDev::StartProgressionEvent(TCHAR_TO_UTF8(*locationName), attributesMap);
}

void UDevToDevBlueprintFunctionLibrary::EndProgressionEvent(const FString& locationName, const TArray<FAnalyticsEventAttr>& Attributes, const TArray<FAnalyticsEventAttr>& Earned, const TArray<FAnalyticsEventAttr>& Spent)
{
	std::map<std::string, std::string> attributesMap = AttributesToMap(Attributes);
	std::map<std::string, std::string> earnedMap = AttributesToMap(Earned);
	std::map<std::string, std::string> spentMap = AttributesToMap(Spent);
    
    devtodev::DevToDev::EndProgressionEvent(TCHAR_TO_UTF8(*locationName), attributesMap, earnedMap, spentMap);
}