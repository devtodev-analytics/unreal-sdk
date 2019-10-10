// Copyright 2018-2019 devtodev. All Rights Reserved.

#include "AnalyticsIOSImplementation.h"

#import <devtodev/devtodev.h>

#include "IOSTransformations.h"
#include "PeopleIOSImplementation.h"

using namespace std;
using namespace devtodev;

AnalyticsIOSImplementation::AnalyticsIOSImplementation(): DTDAnalyticsImplementation() {
    delete people;
    people = new PeopleIOSImplementation();
}

AnalyticsIOSImplementation::~AnalyticsIOSImplementation() {
    
}

void AnalyticsIOSImplementation::initialize(const string& appKey, const string& appSecret) {
    return [::DevToDev initWithKey:transform(appKey) andSecretKey:transform(appSecret)];
}

void AnalyticsIOSImplementation::sendBufferedEvents() {
    return [::DevToDev sendBufferedEvents];
}

void AnalyticsIOSImplementation::customEvent(const string& name) {
    return [::DevToDev customEvent:transform(name)];
}

void AnalyticsIOSImplementation::customEvent(const string& name, const map<string, string>& params) {
    CustomEventParams * param = [[CustomEventParams alloc] init];
    
    for (auto pair : params) {
        [param putParam:transform(pair.first) withString:transform(pair.second)];
    }
    
    return [::DevToDev customEvent:transform(name) withParams:param];
}

void AnalyticsIOSImplementation::startProgressionEvent(const string& locationName, const map<string, string>& params) {
    map<string, string> earned;
    map<string, string> spent;
    
    LocationEventParams * startParams = transformLocationEventParams(params, earned, spent);
    return [::DevToDev startProgressionEvent:transform(locationName) withParameters:startParams];
}

void AnalyticsIOSImplementation::endProgressionEvent(const string& locationName, const map<string, string>& params, const map<string, string>& earned, const map<string, string>& spent) {
    LocationEventParams * endParams = transformLocationEventParams(params, earned, spent);
    return [::DevToDev endProgressionEvent:transform(locationName) withParameters:endParams];
}

void AnalyticsIOSImplementation::currencyAccrual(int amount, const string& currencyName, DTDAccrualType accrualType) {
    return [::DevToDev currencyAccrual:amount withCurrencyName:transform(currencyName) andCurrencyType:(AccrualType)accrualType];
}

void AnalyticsIOSImplementation::inAppPurchase(const string& purchaseId, const string& purchaseType, int purchaseAmount, int purchasePrice, const string& purchaseCurrency) {
    return [::DevToDev inAppPurchase:transform(purchaseId) withPurchaseType:transform(purchaseType) andPurchaseAmount:purchaseAmount andPurchasePrice:purchasePrice andPurchaseCurrency:transform(purchaseCurrency)];
}

//TODO IAP Params

void AnalyticsIOSImplementation::tutorialCompleted(int state) {
    return [::DevToDev tutorialCompleted:state];
}

void AnalyticsIOSImplementation::levelUp(int level) {
    return [::DevToDev levelUp:level];
}

void AnalyticsIOSImplementation::levelUp(int level, const map<string, int>& resourses) {
    return [::DevToDev levelUp:level withResources:transform(resourses)];
}

void AnalyticsIOSImplementation::setCurrentLevel(int level) {
    return [::DevToDev setCurrentLevel:level];
}

void AnalyticsIOSImplementation::realPayment(const string& transactionId, float inAppPrice, const string& inAppName, const string& inAppCurrencyISOCode) {
    return [::DevToDev realPayment:transform(transactionId) withInAppPrice:inAppPrice andInAppName:transform(inAppName) andInAppCurrencyISOCode:transform(inAppCurrencyISOCode)];
}

void AnalyticsIOSImplementation::socialNetworkConnect(const string& name) {
    return [::DevToDev socialNetworkConnect:[SocialNetwork Custom:transform(name)]];
}

void AnalyticsIOSImplementation::socialNetworkPost(const string& name, const string& reason) {
    return [::DevToDev socialNetworkPost:[SocialNetwork Custom:transform(name)] withReason:transform(reason)];
}

void AnalyticsIOSImplementation::setUserId(const string& name) {
    return [::DevToDev setUserId:transform(name)];
}

void AnalyticsIOSImplementation::replaceUserId(const string& from, const string& to) {
    return [::DevToDev replaceUserId:transform(from) to:transform(to)];
}

void AnalyticsIOSImplementation::referrer(const map<string, string>& entries) {
    NSDictionary * input = transform(entries);
    NSMutableDictionary * output = [[NSMutableDictionary alloc] init];
    for(NSString * key in input) {
        NSString * adKey = key;
        if ([[key lowercaseString] isEqualToString:@"source"]) {
            adKey = @"publisher";
        } else if ([[key lowercaseString] isEqualToString:@"medium"]) {
            adKey = @"subplacement";
        } else if ([[key lowercaseString] isEqualToString:@"content"]) {
            adKey = @"subad";
        } else if ([[key lowercaseString] isEqualToString:@"campaign"]) {
            adKey = @"subcampaign";
        } else if ([[key lowercaseString] isEqualToString:@"term"]) {
            adKey = @"subkeyword";
        }
        ReferralProperty *propertyKey = [ReferralProperty Custom:adKey];
        [output setObject:[input objectForKey:key] forKey:propertyKey];
    }
    [::DevToDev referrer:output];
}

void AnalyticsIOSImplementation::setTrackingAvailability(bool isAllowed) {
    return [::DevToDev setTrackingAvailability:transform(isAllowed)];
}

void AnalyticsIOSImplementation::setActiveLog(bool isActive) {
    return [::DevToDev setActiveLog:transform(isActive)];
}

const char * AnalyticsIOSImplementation::getUserId() {
    return transform([::DevToDev getUserId]);
}