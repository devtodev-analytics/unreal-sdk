#pragma once

#include "AnalyticsBlueprintLibrary.h"
#include "PeopleLibrary.generated.h"

UCLASS()
class DEVTODEV_API UPeopleLibrary : public UBlueprintFunctionLibrary {
    GENERATED_BODY()

  public:
    UFUNCTION(BlueprintCallable, Category = "Analytics|People")
    static void Cheater(bool cheater);

    UFUNCTION(BlueprintCallable, Category = "Analytics|People")
    static void Age(int32 age);

    UFUNCTION(BlueprintCallable, Category = "Analytics|People")
    static void Gender(const FString& InGender);

    UFUNCTION(BlueprintCallable, Category = "Analytics|People")
    static void Email(const FString& email);

    UFUNCTION(BlueprintCallable, Category = "Analytics|People")
    static void Phone(const FString& phone);

    UFUNCTION(BlueprintCallable, Category = "Analytics|People")
    static void Photo(const FString& photo);

    UFUNCTION(BlueprintCallable, Category = "Analytics|People")
    static void Name(const FString& photo);

    UFUNCTION(BlueprintCallable, Category = "Analytics|People")
    static void SetUserData(const TArray<FAnalyticsEventAttr>& Attributes);

    UFUNCTION(BlueprintCallable, Category = "Analytics|People")
    static void UnsetUserData(const TArray<FString>& Attributes);

    UFUNCTION(BlueprintCallable, Category = "Analytics|People")
    static void ClearUserData();

    UFUNCTION(BlueprintCallable, Category = "Analytics|People")
    static void IncrementUserData(const TArray<FAnalyticsEventAttr>& Attributes);

    UFUNCTION(BlueprintCallable, Category = "Analytics|People")
    static void AppendUserData(const TArray<FAnalyticsEventAttr>& Attributes);

    UFUNCTION(BlueprintCallable, Category = "Analytics|People")
    static void UnionUserData(const TArray<FAnalyticsEventAttr>& Attributes);
};
