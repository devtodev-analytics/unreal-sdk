// Copyright 2018-2020 devtodev. All Rights Reserved.

#pragma once

#include "AnalyticsBlueprintLibrary.h"
#include "UObject/Object.h"
#include "DTDAnalyticsBlueprintFunctionLibrary.generated.h"

class UPeopleLibrary;

UCLASS()
class DEVTODEV_API UDTDAnalyticsBlueprintFunctionLibrary : public UObject {
    GENERATED_UCLASS_BODY()

  public:
    UFUNCTION(BlueprintCallable, Category = "Analytics")
    static void SetTrackingAvailability(bool trackingAllowed);

    UFUNCTION(BlueprintCallable, Category = "Analytics")
    static void TutorialCompleted(int32 step);

    UFUNCTION(BlueprintCallable, Category = "Analytics")
    static void LevelUp(int32 level);

    UFUNCTION(BlueprintCallable, Category = "Analytics", meta = (DisplayName = "Level Up With Attributes"))
    static void LevelUpWithAttributes(int32 level, const TArray<FAnalyticsEventAttr>& Attributes);

    UFUNCTION(BlueprintCallable, Category = "Analytics")
    static void SetCurrentLevel(int32 level);

    UFUNCTION(BlueprintCallable, Category = "Analytics")
    static void SocialNetworkConnect(const FString& socialName);

    UFUNCTION(BlueprintCallable, Category = "Analytics")
    static void SocialNetworkPost(const FString& socialName, const FString& reason);

    UFUNCTION(BlueprintCallable, Category = "Analytics")
    static void ReplaceUserId(const FString& from, const FString& to);

    UFUNCTION(BlueprintCallable, Category = "Analytics")
    static void RealPayment(const FString& transactionId, float inAppPrice, const FString& inAppName, const FString& inAppCurrencyISOCode);

    UFUNCTION(BlueprintCallable, Category = "Analytics")
    static void Referrer(const TArray<FAnalyticsEventAttr>& Attributes);

    UFUNCTION(BlueprintCallable, Category = "Analytics")
    static void StartProgressionEvent(const FString& locationName, const TArray<FAnalyticsEventAttr>& Attributes);

    UFUNCTION(BlueprintCallable, Category = "Analytics")
    static void EndProgressionEvent(const FString& locationName, const TArray<FAnalyticsEventAttr>& Attributes, const TArray<FAnalyticsEventAttr>& Earned,
                                    const TArray<FAnalyticsEventAttr>& Spent);

    UFUNCTION(BlueprintCallable, Category = "Analytics")
    static void SetPushNotificationsEnabled(bool isEnabled);
};
