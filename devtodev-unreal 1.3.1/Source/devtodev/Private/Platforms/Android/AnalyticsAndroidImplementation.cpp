// Copyright 2018-2019 devtodev. All Rights Reserved.

#include "AnalyticsAndroidImplementation.h"

#include "DevToDevJNI.h"
#include "PeopleAndroidImplementation.h"

using namespace std;
using namespace devtodev;

AnalyticsAndroidImplementation::AnalyticsAndroidImplementation() : DTDAnalyticsImplementation() {
    delete people;
    people = new PeopleAndroidImplementation();
}

AnalyticsAndroidImplementation::~AnalyticsAndroidImplementation() {
}

void AnalyticsAndroidImplementation::initialize(const std::string& appKey, const std::string& appSecret) {
    jni_initialize(appKey, appSecret);
}

void AnalyticsAndroidImplementation::sendBufferedEvents() {
    jni_sendBufferedEvents();
}

void AnalyticsAndroidImplementation::customEvent(const std::string& name) {
    std::map<std::string, std::string> params;
    jni_customEvent(name, params);
}

void AnalyticsAndroidImplementation::customEvent(const std::string& name, const std::map<std::string, std::string>& params) {
    jni_customEvent(name, params);
}

void AnalyticsAndroidImplementation::startProgressionEvent(const std::string& locationName, const std::map<std::string, std::string>& params) {
    jni_startProgressionEvent(locationName, params);
}

void AnalyticsAndroidImplementation::endProgressionEvent(const std::string& locationName, const std::map<std::string, std::string>& params,
                                                         const std::map<std::string, std::string>& earned, const std::map<std::string, std::string>& spent) {
    jni_endProgressionEvent(locationName, params, earned, spent);
}

void AnalyticsAndroidImplementation::currencyAccrual(int amount, const std::string& currencyName, DTDAccrualType accrualType) {
    jni_currencyAccrual(amount, currencyName, accrualType);
}

void AnalyticsAndroidImplementation::inAppPurchase(const std::string& purchaseId, const std::string& purchaseType, int purchaseAmount, int purchasePrice,
                                                   const std::string& purchaseCurrency) {
    jni_inAppPurchase(purchaseId, purchaseType, purchaseAmount, purchasePrice, purchaseCurrency);
}

// TODO IAP Params

void AnalyticsAndroidImplementation::tutorialCompleted(int state) {
    jni_tutorialCompleted(state);
}

void AnalyticsAndroidImplementation::levelUp(int level) {
    std::map<std::string, int> params;
    jni_levelUp(level, params);
}

void AnalyticsAndroidImplementation::levelUp(int level, const std::map<std::string, int>& resourses) {
    jni_levelUp(level, resourses);
}

void AnalyticsAndroidImplementation::setCurrentLevel(int level) {
    jni_setCurrentLevel(level);
}

void AnalyticsAndroidImplementation::realPayment(const std::string& transactionId, float inAppPrice, const std::string& inAppName,
                                                 const std::string& inAppCurrencyISOCode) {
    jni_realPayment(transactionId, inAppPrice, inAppName, inAppCurrencyISOCode);
}

void AnalyticsAndroidImplementation::socialNetworkConnect(const std::string& name) {
    jni_socialNetworkConnect(name);
}

void AnalyticsAndroidImplementation::socialNetworkPost(const std::string& name, const std::string& reason) {
    jni_socialNetworkPost(name, reason);
}

void AnalyticsAndroidImplementation::setUserId(const std::string& name) {
    jni_setUserId(name);
}

void AnalyticsAndroidImplementation::replaceUserId(const std::string& from, const std::string& to) {
    jni_replaceUserId(from, to);
}

void AnalyticsAndroidImplementation::referrer(const std::map<std::string, std::string>& entries) {
    jni_referrer(entries);
}

void AnalyticsAndroidImplementation::setTrackingAvailability(bool isAllowed) {
    jni_setTrackingAvailability(isAllowed);
}

void AnalyticsAndroidImplementation::setActiveLog(bool isActive) {
    jni_setActiveLog(isActive);
}

const char* AnalyticsAndroidImplementation::getUserId() {
    return jni_getUserId();
}
