// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AnalyticsBlueprintLibrary.h"
#include "DevToDevBlueprintFunctionLibrary.generated.h"

class UPeopleLibrary;

UCLASS()
class DEVTODEV_API UDevToDevBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Analytics")
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
    static void SocialNetworkPost(const FString& socialName, const FString & reason);

    UFUNCTION(BlueprintCallable, Category = "Analytics")
    static void ReplaceUserId(const FString& from, const FString& to);

    UFUNCTION(BlueprintCallable, Category = "Analytics")
    static void RealPayment(const FString& transactionId, float inAppPrice, const FString& inAppName, const FString& inAppCurrencyISOCode);
    
    UFUNCTION(BlueprintCallable, Category = "Analytics")
    static void Referrer(const TArray<FAnalyticsEventAttr>& Attributes);
};
