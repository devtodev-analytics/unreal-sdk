#pragma once

#include <string>
#include <map>
#include <vector>

#if PLATFORM_IOS
#import <Foundation/Foundation.h>

@interface DevToDevUE4 : NSObject
+(id) sharedInstance;
@end
#endif

namespace devtodev {
	enum DTDGender
	{
		DTDUnknown = 0,
		DTDMale = 1,
		DTDFemale = 2
	};

	enum DTDAccrualType
	{
		DTDEarned, 
		DTDPurchased
	};
    
    class People
    {
    public:
        static void Cheater(bool cheater);
        
        static void Age(int age);
        
        static void Gender(DTDGender dtdGender);
        
        static void Email(const std::string& email);
        
        static void Phone(const std::string& phone);
        
        static void Photo(const std::string& photo);
        
        static void Name(const std::string& photo);
        
        static void SetUserData(const std::map<std::string, std::string>& Attributes);
        
        static void UnsetUserData(const std::vector<std::string>& Attributes);
        
        static void ClearUserData();
        
        static void IncrementUserData(const std::map<std::string, std::string>& Attributes);
        
        static void AppendUserData(const std::map<std::string, std::string>& Attributes);
        
        static void UnionUserData(const std::map<std::string, std::string>& Attributes);
        
    };

	class DevToDev
	{
	public:
		static void SetActiveLog(bool isActive);

    	static void Initialize(const std::string& appKey, const std::string& appSecret);

    	static void SendBufferedEvents();
    
    	static void CustomEvent(const std::string& name);

    	static void CustomEvent(const std::string& name, const std::map<std::string, std::string>& params);

    	static void StartProgressionEvent(const std::string& locationName, const std::map<std::string, std::string>& params);

    	static void EndProgressionEvent(const std::string& locationName, const std::map<std::string, std::string>& params, const std::map<std::string, std::string>& earned, const std::map<std::string, std::string>& spent);

    	static void CurrencyAccrual(int amount, const std::string& currencyName, DTDAccrualType accrualType);

    	static void InAppPurchase(const std::string& purchaseId, const std::string& purchaseType, int purchaseAmount, int purchasePrice, const std::string& purchaseCurrency); 
    
    	//TODO IAP Params

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

	    static const char * GetUserId();
        
        static People ActivePeople();
	};

	class DevToDevPushManager
	{
	public:
		static void SetDelegate();
	};
}