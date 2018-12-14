#include "DTDWrapper.h"
#include "CoreMinimal.h"

#if PLATFORM_IOS
#include "Platforms/IOS/AnalyticsIOSImplementation.h"
#include "Platforms/IOS/MessagingIOSImplementation.h"
#elif PLATFORM_ANDROID
#include "Platforms/Android/AnalyticsAndroidImplementation.h"
#include "Platforms/Android/MessagingAndroidImplementation.h"
#endif

#include "Analytics/DTDPeopleImplementation.h"

using namespace std;
using namespace devtodev;

// DTDWrapper

DTDWrapper::DTDWrapper() {
#if PLATFORM_IOS
    analytics = new AnalyticsIOSImplementation();
    messaging = new MessagingIOSImplementation();
#elif PLATFORM_ANDROID
    analytics = new AnalyticsAndroidImplementation();
    messaging = new MessagingAndroidImplementation();
#else
    analytics = new DTDAnalyticsImplementation();
    messaging = new DTDMessagingImplementation();
#endif
}

DTDWrapper::~DTDWrapper() {
    delete analytics;
    delete messaging;
}

DTDAnalyticsImplementation* DTDWrapper::getAnalytics() {
    return analytics;
}

DTDMessagingImplementation* DTDWrapper::getMessaging() {
    return messaging;
}

// DTDAnalytics

void DTDAnalytics::Initialize(const string& appKey, const string& appSecret) {
    DTDWrapper::getInstance().getAnalytics()->initialize(appKey, appSecret);
}

void DTDAnalytics::SendBufferedEvents() {
    DTDWrapper::getInstance().getAnalytics()->sendBufferedEvents();
}

void DTDAnalytics::CustomEvent(const string& name) {
    DTDWrapper::getInstance().getAnalytics()->customEvent(name);
}

void DTDAnalytics::CustomEvent(const string& name, const map<string, string>& params) {
    DTDWrapper::getInstance().getAnalytics()->customEvent(name, params);
}

void DTDAnalytics::StartProgressionEvent(const string& locationName, const map<string, string>& params) {
    DTDWrapper::getInstance().getAnalytics()->startProgressionEvent(locationName, params);
}

void DTDAnalytics::EndProgressionEvent(const string& locationName, const map<string, string>& params, const map<string, string>& earned,
                                       const map<string, string>& spent) {
    DTDWrapper::getInstance().getAnalytics()->endProgressionEvent(locationName, params, earned, spent);
}

void DTDAnalytics::CurrencyAccrual(int amount, const string& currencyName, DTDAccrualType accrualType) {
    DTDWrapper::getInstance().getAnalytics()->currencyAccrual(amount, currencyName, accrualType);
}

void DTDAnalytics::InAppPurchase(const string& purchaseId, const string& purchaseType, int purchaseAmount, int purchasePrice, const string& purchaseCurrency) {
    DTDWrapper::getInstance().getAnalytics()->inAppPurchase(purchaseId, purchaseType, purchaseAmount, purchasePrice, purchaseCurrency);
}

// TODO IAP Params
void DTDAnalytics::TutorialCompleted(int state) {
    DTDWrapper::getInstance().getAnalytics()->tutorialCompleted(state);
}

void DTDAnalytics::LevelUp(int level) {
    DTDWrapper::getInstance().getAnalytics()->levelUp(level);
}

void DTDAnalytics::LevelUp(int level, const map<string, int>& resourses) {
    DTDWrapper::getInstance().getAnalytics()->levelUp(level, resourses);
}

void DTDAnalytics::SetCurrentLevel(int level) {
    DTDWrapper::getInstance().getAnalytics()->setCurrentLevel(level);
}

void DTDAnalytics::RealPayment(const string& transactionId, float inAppPrice, const string& inAppName, const string& inAppCurrencyISOCode) {
    DTDWrapper::getInstance().getAnalytics()->realPayment(transactionId, inAppPrice, inAppName, inAppCurrencyISOCode);
}

void DTDAnalytics::SocialNetworkConnect(const string& name) {
    DTDWrapper::getInstance().getAnalytics()->socialNetworkConnect(name);
}

void DTDAnalytics::SocialNetworkPost(const string& name, const string& reason) {
    DTDWrapper::getInstance().getAnalytics()->socialNetworkPost(name, reason);
}

void DTDAnalytics::SetUserId(const string& name) {
    DTDWrapper::getInstance().getAnalytics()->setUserId(name);
}

void DTDAnalytics::ReplaceUserId(const string& from, const string& to) {
    DTDWrapper::getInstance().getAnalytics()->replaceUserId(from, to);
}

void DTDAnalytics::Referrer(const map<string, string>& entries) {
    DTDWrapper::getInstance().getAnalytics()->referrer(entries);
}

void DTDAnalytics::SetTrackingAvailability(bool isAllowed) {
    DTDWrapper::getInstance().getAnalytics()->setTrackingAvailability(isAllowed);
}

void DTDAnalytics::SetActiveLog(bool isActive) {
    DTDWrapper::getInstance().getAnalytics()->setActiveLog(isActive);
}

const char* DTDAnalytics::GetUserId() {
    return DTDWrapper::getInstance().getAnalytics()->getUserId();
}

DTDPeopleImplementation* DTDAnalytics::GetActivePeople() {
    return DTDWrapper::getInstance().getAnalytics()->getActivePeople();
}

// DTDMessaging

void DTDMessaging::SetPushNotificationsEnabled(bool isEnabled) {
    DTDWrapper::getInstance().getMessaging()->setPushNotificationsEnabled(isEnabled);
}