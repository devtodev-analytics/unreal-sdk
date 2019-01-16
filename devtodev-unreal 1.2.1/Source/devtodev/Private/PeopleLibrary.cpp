// Copyright 2018-2019 devtodev. All Rights Reserved.

#include "PeopleLibrary.h"
#include "DTDWrapper.h"
#include "DevToDevPrivatePCH.h"

#include "Analytics/DTDPeopleImplementation.h"

#include <map>
#include <string>

using namespace devtodev;

void UPeopleLibrary::Cheater(bool cheater) {
    DTDAnalytics::GetActivePeople()->cheater(cheater);
}

void UPeopleLibrary::Age(int32 age) {
    DTDAnalytics::GetActivePeople()->age(age);
}

void UPeopleLibrary::Gender(const FString& InGender) {
    DTDGender gender = DTDUnknown;

    if (InGender.Equals("male", ESearchCase::IgnoreCase)) {
        gender = devtodev::DTDMale;
    } else if (InGender.Equals("female", ESearchCase::IgnoreCase)) {
        gender = devtodev::DTDFemale;
    }

    DTDAnalytics::GetActivePeople()->gender(gender);
}

void UPeopleLibrary::Email(const FString& email) {
    DTDAnalytics::GetActivePeople()->email(TCHAR_TO_UTF8(*email));
}

void UPeopleLibrary::Phone(const FString& phone) {
    DTDAnalytics::GetActivePeople()->phone(TCHAR_TO_UTF8(*phone));
}

void UPeopleLibrary::Name(const FString& phone) {
    DTDAnalytics::GetActivePeople()->name(TCHAR_TO_UTF8(*phone));
}

void UPeopleLibrary::Photo(const FString& photo) {
    DTDAnalytics::GetActivePeople()->photo(TCHAR_TO_UTF8(*photo));
}

void UPeopleLibrary::SetUserData(const TArray<FAnalyticsEventAttr>& Attributes) {
    const int32 AttrCount = Attributes.Num();
    if (AttrCount > 0) {
        std::map<std::string, std::string> params;
        for (int32 Index = 0; Index < Attributes.Num(); Index++) {
            params[TCHAR_TO_UTF8(*Attributes[Index].Name)] = TCHAR_TO_UTF8(*Attributes[Index].Value);
        }
        DTDAnalytics::GetActivePeople()->setUserData(params);
    }
}

void UPeopleLibrary::UnsetUserData(const TArray<FString>& Attributes) {
    if (Attributes.Num() > 0) {
        std::vector<std::string> params;
        for (int32 Index = 0; Index < Attributes.Num(); Index++) {
            params.push_back(TCHAR_TO_UTF8(*Attributes[Index]));
        }
        DTDAnalytics::GetActivePeople()->unsetUserData(params);
    }
}

void UPeopleLibrary::ClearUserData() {
    DTDAnalytics::GetActivePeople()->clearUserData();
}

void UPeopleLibrary::IncrementUserData(const TArray<FAnalyticsEventAttr>& Attributes) {
    const int32 AttrCount = Attributes.Num();
    if (AttrCount > 0) {
        std::map<std::string, int> params;
        for (int32 Index = 0; Index < Attributes.Num(); Index++) {
            params[TCHAR_TO_UTF8(*Attributes[Index].Name)] = FCString::Atoi(*Attributes[Index].Value);
        }
        DTDAnalytics::GetActivePeople()->incrementUserData(params);
    }
}

void UPeopleLibrary::AppendUserData(const TArray<FAnalyticsEventAttr>& Attributes) {
    const int32 AttrCount = Attributes.Num();
    if (AttrCount > 0) {
        std::map<std::string, std::string> params;
        for (int32 Index = 0; Index < Attributes.Num(); Index++) {
            params[TCHAR_TO_UTF8(*Attributes[Index].Name)] = TCHAR_TO_UTF8(*Attributes[Index].Value);
        }
        DTDAnalytics::GetActivePeople()->appendUserData(params);
    }
}

void UPeopleLibrary::UnionUserData(const TArray<FAnalyticsEventAttr>& Attributes) {
    const int32 AttrCount = Attributes.Num();
    if (AttrCount > 0) {
        std::map<std::string, std::string> params;
        for (int32 Index = 0; Index < Attributes.Num(); Index++) {
            params[TCHAR_TO_UTF8(*Attributes[Index].Name)] = TCHAR_TO_UTF8(*Attributes[Index].Value);
        }
        DTDAnalytics::GetActivePeople()->unionUserData(params);
    }
}
