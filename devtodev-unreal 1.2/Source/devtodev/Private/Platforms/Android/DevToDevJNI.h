#ifndef DevToDevJNI_h
#define DevToDevJNI_h

#include <map>
#include <string>
#include <vector>

#include "../../Analytics/DTDPeopleImplementation.h"
#include "../../Analytics/DTDAnalyticsImplementation.h"

namespace devtodev {
    extern "C" {
    extern void jni_initialize(const std::string& appKey, const std::string& appSecret);
    extern void jni_setActiveLog(bool isActive);
    extern void jni_sendBufferedEvents();
    extern void jni_customEvent(const std::string& name, const std::map<std::string, std::string>& params);
    extern void jni_startProgressionEvent(const std::string& locationName, const std::map<std::string, std::string>& params);
    extern void jni_endProgressionEvent(const std::string& locationName, const std::map<std::string, std::string>& params,
                                        const std::map<std::string, std::string>& earned, const std::map<std::string, std::string>& spent);
    extern void jni_currencyAccrual(int amount, const std::string& currencyName, DTDAccrualType accrualType);
    extern void jni_inAppPurchase(const std::string& purchaseId, const std::string& purchaseType, int purchaseAmount, int purchasePrice,
                                  const std::string& purchaseCurrency);
    extern void jni_tutorialCompleted(int state);
    extern void jni_levelUp(int level, const std::map<std::string, int>& resourses);
    extern void jni_setCurrentLevel(int level);
    extern void jni_realPayment(const std::string& transactionId, float inAppPrice, const std::string& inAppName, const std::string& inAppCurrencyISOCode);
    extern void jni_socialNetworkConnect(const std::string& name);
    extern void jni_socialNetworkPost(const std::string& name, const std::string& reason);
    extern void jni_setUserId(const std::string& name);
    extern void jni_replaceUserId(const std::string& from, const std::string& to);
    extern void jni_referrer(const std::map<std::string, std::string>& entries);
    extern void jni_setTrackingAvailability(bool isAllowed);
    extern void jni_setActiveLog(bool isActive);
    extern const char* jni_getUserId();

    extern void jni_people_cheater(bool cheater);
    extern void jni_people_age(int age);
    extern void jni_people_gender(DTDGender gender);
    extern void jni_people_email(const std::string& email);
    extern void jni_people_phone(const std::string& phone);
    extern void jni_people_photo(const std::string& photo);
    extern void jni_people_name(const std::string& name);
    extern void jni_people_setUserData(const std::map<std::string, std::string>& Attributes);
    extern void jni_people_unsetUserData(const std::vector<std::string>& Attributes);
    extern void jni_people_clearUserData();
    extern void jni_people_incrementUserData(const std::map<std::string, int>& Attributes);
    extern void jni_people_appendUserData(const std::map<std::string, std::string>& Attributes);
    extern void jni_people_unionUserData(const std::map<std::string, std::string>& Attributes);
    }
} // namespace devtodev

#endif /* DevToDevJNI_h */
