#ifndef AnalyticsIOSImplementation_hpp
#define AnalyticsIOSImplementation_hpp

#include "../../Analytics/DTDAnalyticsImplementation.h"

namespace devtodev {
    class AnalyticsIOSImplementation : public DTDAnalyticsImplementation {
      public:
        explicit AnalyticsIOSImplementation();
        virtual ~AnalyticsIOSImplementation();

        virtual void initialize(const std::string& appKey, const std::string& appSecret);

        virtual void sendBufferedEvents();

        virtual void customEvent(const std::string& name);

        virtual void customEvent(const std::string& name, const std::map<std::string, std::string>& params);

        virtual void startProgressionEvent(const std::string& locationName, const std::map<std::string, std::string>& params);

        virtual void endProgressionEvent(const std::string& locationName, const std::map<std::string, std::string>& params,
                                         const std::map<std::string, std::string>& earned, const std::map<std::string, std::string>& spent);

        virtual void currencyAccrual(int amount, const std::string& currencyName, DTDAccrualType accrualType);

        virtual void inAppPurchase(const std::string& purchaseId, const std::string& purchaseType, int purchaseAmount, int purchasePrice,
                                   const std::string& purchaseCurrency);

        // TODO IAP Params

        virtual void tutorialCompleted(int state);

        virtual void levelUp(int level);

        virtual void levelUp(int level, const std::map<std::string, int>& resourses);

        virtual void setCurrentLevel(int level);

        virtual void realPayment(const std::string& transactionId, float inAppPrice, const std::string& inAppName, const std::string& inAppCurrencyISOCode);

        virtual void socialNetworkConnect(const std::string& name);

        virtual void socialNetworkPost(const std::string& name, const std::string& reason);

        virtual void setUserId(const std::string& name);

        virtual void replaceUserId(const std::string& from, const std::string& to);

        virtual void referrer(const std::map<std::string, std::string>& entries);

        virtual void setTrackingAvailability(bool isAllowed);

        virtual void setActiveLog(bool isActive);

        virtual const char* getUserId();
    };
} // namespace devtodev

#endif /* AnalyticsIOSImplementation_hpp */
