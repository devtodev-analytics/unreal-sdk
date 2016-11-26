#include "DevToDevPrivatePCH.h"
#include "PeopleLibrary.h"
#include "DevToDev.h"

#include <map>
#include <string>

void UPeopleLibrary::Cheater(bool cheater)
{
    devtodev::DevToDev::ActivePeople().Cheater(cheater);
}

void UPeopleLibrary::Age(int32 age)
{
    devtodev::DevToDev::ActivePeople().Age(age);
}

void UPeopleLibrary::Gender(const FString& InGender)
{
    devtodev::DTDGender gender = devtodev::DTDUnknown;
    
    if (InGender.Equals("male", ESearchCase::IgnoreCase))
    {
        gender = devtodev::DTDMale;
    } else if (InGender.Equals("female", ESearchCase::IgnoreCase))
    {
        gender = devtodev::DTDFemale;
    }
    
    devtodev::DevToDev::ActivePeople().Gender(gender);
}

void UPeopleLibrary::Email(const FString& email)
{
    devtodev::DevToDev::ActivePeople().Email(TCHAR_TO_UTF8(*email));
}

void UPeopleLibrary::Phone(const FString& phone)
{
    devtodev::DevToDev::ActivePeople().Phone(TCHAR_TO_UTF8(*phone));
}

void UPeopleLibrary::Name(const FString& phone)
{
    devtodev::DevToDev::ActivePeople().Name(TCHAR_TO_UTF8(*phone));
}

void UPeopleLibrary::Photo(const FString& photo)
{
    devtodev::DevToDev::ActivePeople().Photo(TCHAR_TO_UTF8(*photo));
}

void UPeopleLibrary::SetUserData(const TArray<FAnalyticsEventAttr>& Attributes)
{
    const int32 AttrCount = Attributes.Num();
    if (AttrCount > 0) {
        std::map<std::string, std::string> params;
        for (int32 Index = 0; Index < Attributes.Num(); Index++)
        {
            params[TCHAR_TO_UTF8(*Attributes[Index].Name)] = TCHAR_TO_UTF8(*Attributes[Index].Value);
        }
        devtodev::DevToDev::ActivePeople().SetUserData(params);
    }
}

void UPeopleLibrary::UnsetUserData(const TArray<FString>& Attributes)
{
    if (Attributes.Num() > 0) {
        std::vector<std::string> params;
        for (int32 Index = 0; Index < Attributes.Num(); Index++) {
            params.push_back(TCHAR_TO_UTF8(*Attributes[Index]));
        }
        devtodev::DevToDev::ActivePeople().UnsetUserData(params);
    }
}

void UPeopleLibrary::ClearUserData()
{
    devtodev::DevToDev::ActivePeople().ClearUserData();
}

void UPeopleLibrary::IncrementUserData(const TArray<FAnalyticsEventAttr>& Attributes)
{
    const int32 AttrCount = Attributes.Num();
    if (AttrCount > 0) {
        std::map<std::string, std::string> params;
        for (int32 Index = 0; Index < Attributes.Num(); Index++)
        {
            params[TCHAR_TO_UTF8(*Attributes[Index].Name)] = TCHAR_TO_UTF8(*Attributes[Index].Value);
        }
        devtodev::DevToDev::ActivePeople().IncrementUserData(params);
    }
}

void UPeopleLibrary::AppendUserData(const TArray<FAnalyticsEventAttr>& Attributes)
{
    const int32 AttrCount = Attributes.Num();
    if (AttrCount > 0) {
        std::map<std::string, std::string> params;
        for (int32 Index = 0; Index < Attributes.Num(); Index++)
        {
            params[TCHAR_TO_UTF8(*Attributes[Index].Name)] = TCHAR_TO_UTF8(*Attributes[Index].Value);
        }
        devtodev::DevToDev::ActivePeople().AppendUserData(params);
    }
}

void UPeopleLibrary::UnionUserData(const TArray<FAnalyticsEventAttr>& Attributes)
{
    const int32 AttrCount = Attributes.Num();
    if (AttrCount > 0) {
        std::map<std::string, std::string> params;
        for (int32 Index = 0; Index < Attributes.Num(); Index++)
        {
            params[TCHAR_TO_UTF8(*Attributes[Index].Name)] = TCHAR_TO_UTF8(*Attributes[Index].Value);
        }
        devtodev::DevToDev::ActivePeople().UnionUserData(params);
    }
}