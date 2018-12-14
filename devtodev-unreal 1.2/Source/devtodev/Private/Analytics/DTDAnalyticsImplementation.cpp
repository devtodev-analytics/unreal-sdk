#include "DTDAnalyticsImplementation.h"
#include "DTDPeopleImplementation.h"

using namespace std;
using namespace devtodev;

DTDAnalyticsImplementation::DTDAnalyticsImplementation() {
    people = new DTDPeopleImplementation();
}

DTDAnalyticsImplementation::~DTDAnalyticsImplementation() {
    delete people;
}

void DTDAnalyticsImplementation::initialize(const string& appKey, const string& appSecret) {
}

void DTDAnalyticsImplementation::sendBufferedEvents() {
}

void DTDAnalyticsImplementation::customEvent(const string& name) {
}

void DTDAnalyticsImplementation::customEvent(const string& name, const map<string, string>& params) {
}

void DTDAnalyticsImplementation::startProgressionEvent(const string& locationName, const map<string, string>& params) {
}

void DTDAnalyticsImplementation::endProgressionEvent(const string& locationName, const map<string, string>& params, const map<string, string>& earned,
                                                     const map<string, string>& spent) {
}

void DTDAnalyticsImplementation::currencyAccrual(int amount, const string& currencyName, DTDAccrualType accrualType) {
}

void DTDAnalyticsImplementation::inAppPurchase(const string& purchaseId, const string& purchaseType, int purchaseAmount, int purchasePrice,
                                               const string& purchaseCurrency) {
}

// TODO IAP Params

void DTDAnalyticsImplementation::tutorialCompleted(int state) {
}

void DTDAnalyticsImplementation::levelUp(int level) {
}

void DTDAnalyticsImplementation::levelUp(int level, const map<string, int>& resourses) {
}

void DTDAnalyticsImplementation::setCurrentLevel(int level) {
}

void DTDAnalyticsImplementation::realPayment(const string& transactionId, float inAppPrice, const string& inAppName, const string& inAppCurrencyISOCode) {
}

void DTDAnalyticsImplementation::socialNetworkConnect(const string& name) {
}

void DTDAnalyticsImplementation::socialNetworkPost(const string& name, const string& reason) {
}

void DTDAnalyticsImplementation::setUserId(const string& name) {
}

void DTDAnalyticsImplementation::replaceUserId(const string& from, const string& to) {
}

void DTDAnalyticsImplementation::referrer(const map<string, string>& entries) {
}

void DTDAnalyticsImplementation::setTrackingAvailability(bool isAllowed) {
}

void DTDAnalyticsImplementation::setActiveLog(bool isActive) {
}

const char* DTDAnalyticsImplementation::getUserId() {
    return "";
}

DTDPeopleImplementation* DTDAnalyticsImplementation::getActivePeople() {
    return people;
}
