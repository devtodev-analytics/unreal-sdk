#pragma once

#include <map>
#include <string>
#include <vector>

#include "Analytics/DTDAnalyticsImplementation.h"
#include "Messaging/DTDMessagingImplementation.h"

namespace devtodev {

    class DTDPeopleImplementation;
    class DTDAnalyticsImplementation;
    class DTDMessagingImplementation;

    class DTDWrapper {
      public:
        static DTDWrapper& getInstance() {
            static DTDWrapper instance;
            return instance;
        }

        DTDAnalyticsImplementation* getAnalytics();
        DTDMessagingImplementation* getMessaging();

      private:
        DTDWrapper();
        virtual ~DTDWrapper();

        DTDAnalyticsImplementation* analytics;
        DTDMessagingImplementation* messaging;
    };

    class DTDAnalytics {
      public:
        static void Initialize(const std::string& appKey, const std::string& appSecret);
        static void SendBufferedEvents();
        static void CustomEvent(const std::string& name);
        static void CustomEvent(const std::string& name, const std::map<std::string, std::string>& params);
        static void StartProgressionEvent(const std::string& locationName, const std::map<std::string, std::string>& params);
        static void EndProgressionEvent(const std::string& locationName, const std::map<std::string, std::string>& params,
                                        const std::map<std::string, std::string>& earned, const std::map<std::string, std::string>& spent);
        static void CurrencyAccrual(int amount, const std::string& currencyName, DTDAccrualType accrualType);
        static void InAppPurchase(const std::string& purchaseId, const std::string& purchaseType, int purchaseAmount, int purchasePrice,
                                  const std::string& purchaseCurrency);
        // TODO IAP Params
        static void TutorialCompleted(int state);
        static void LevelUp(int level);
        static void LevelUp(int level, const std::map<std::string, int>& resourses);
        static void SetCurrentLevel(int level);
        static void RealPayment(const std::string& transactionId, float inAppPrice, const std::string& inAppName, const std::string& inAppCurrencyISOCode);
        static void SocialNetworkConnect(const std::string& name);
        static void SocialNetworkPost(const std::string& name, const std::string& reason);
        static void SetUserId(const std::string& name);
        static void ReplaceUserId(const std::string& from, const std::string& to);
        static void Referrer(const std::map<std::string, std::string>& entries);
        static void SetTrackingAvailability(bool isAllowed);
        static void SetActiveLog(bool isActive);
        static const char* GetUserId();
        static DTDPeopleImplementation* GetActivePeople();
    };

    class DTDMessaging {
      public:
        static void SetPushNotificationsEnabled(bool isEnabled);
    };

} // namespace devtodev
