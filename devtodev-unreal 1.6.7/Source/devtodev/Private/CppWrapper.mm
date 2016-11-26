#include "./DevToDev.h"

#if PLATFORM_IOS
#include "../DTD-SDK-IOS/core/DevToDev.h" // analytics obj-c interface
#include "../DTD-SDK-IOS/push/DevToDevPushManager.h" // push obj-c interface
#endif

namespace devtodev
{

#if PLATFORM_IOS
    /////////////////////////
    // Obj-c to C++
    /////////////////////////

    const char * transform(NSString * s)
    {
        return [s cStringUsingEncoding:NSUTF8StringEncoding];
    }

    /////////////////////////
    // C++ to Obj-C
    /////////////////////////
    BOOL transform(bool b)
    {
        return b?YES:NO;
    }

    NSInteger transform(int i)
    {
        return NSInteger(i);
    }

    NSNumber* transform(float v)
    {
        return [NSNumber numberWithFloat:v];
    }

    NSNumber* transform(double v)
    {
        return [NSNumber numberWithDouble:v];
    }

    static NSString* transform(const std::string& s)
    {
        return [NSString stringWithUTF8String:s.c_str()];
    }

    NSMutableDictionary* transform(const std::map<std::string, int>& m)
    {
        NSMutableDictionary* dict = [[NSMutableDictionary alloc] init];

        for (auto pair : m)
        {
            [dict setObject:[NSNumber numberWithInt:pair.second] forKey:transform(pair.first)];
        }

        return dict;
    }

#endif

    //////////////////////////////////
    // Implementation of the wrapper
    //////////////////////////////////

    void DevToDev::SetActiveLog(bool isActive)
    {
#if PLATFORM_IOS
        return [::DevToDev setActiveLog:transform(isActive)];
#endif
    }

    void DevToDev::Initialize(const std::string& appKey, const std::string& appSecret)
    {
#if PLATFORM_IOS
        return [::DevToDev initWithKey:transform(appKey) andSecretKey:transform(appSecret)];
#endif
    }

    void DevToDev::SendBufferedEvents()
    {
#if PLATFORM_IOS
        return [::DevToDev sendBufferedEvents];
#endif
    }

    void DevToDev::CustomEvent(const std::string& name)
    {
#if PLATFORM_IOS
        return [::DevToDev customEvent:transform(name)];
#endif
    }

    void DevToDev::CustomEvent(const std::string& name, const std::map<std::string, std::string>& params)
    {
#if PLATFORM_IOS
        CustomEventParams * param = [[CustomEventParams alloc] init];

        for (auto pair : params)
        {
            [param putParam:transform(pair.first) withString:transform(pair.second)];
        }

        [::DevToDev customEvent:transform(name) withParams:param];
#endif
    }

    void DevToDev::CurrencyAccrual(int amount, const std::string& currencyName, DTDAccrualType accrualType)
    {
#if PLATFORM_IOS
        return [::DevToDev currencyAccrual:amount withCurrencyName:transform(currencyName) andCurrencyType:(AccrualType)accrualType];
#endif
    }

    void DevToDev::InAppPurchase(const std::string& purchaseId, const std::string& purchaseType, int purchaseAmount, int purchasePrice, const std::string& purchaseCurrency)
    {
#if PLATFORM_IOS
        return [::DevToDev inAppPurchase:transform(purchaseId) withPurchaseType:transform(purchaseType) andPurchaseAmount:purchaseAmount andPurchasePrice:purchasePrice andPurchaseCurrency:transform(purchaseCurrency)];
#endif
    }

    //TODO IAP Params

    void DevToDev::TutorialCompleted(int state)
    {
#if PLATFORM_IOS
        return [::DevToDev tutorialCompleted:state];
#endif
    }

    void DevToDev::LevelUp(int level)
    {
#if PLATFORM_IOS
        return [::DevToDev levelUp:level];
#endif
    }

    void DevToDev::LevelUp(int level, const std::map<std::string, int>& resourses)
    {
#if PLATFORM_IOS
        [::DevToDev levelUp:level withResources:transform(resourses)];
#endif
    }

    void DevToDev::SetCurrentLevel(int level)
    {
#if PLATFORM_IOS
        return [::DevToDev setCurrentLevel:level];
#endif
    }

    void DevToDev::RealPayment(const std::string& transactionId, float inAppPrice, const std::string& inAppName, const std::string& inAppCurrencyISOCode)
    {
#if PLATFORM_IOS
        return [::DevToDev realPayment:transform(transactionId) withInAppPrice:inAppPrice andInAppName:transform(inAppName) andInAppCurrencyISOCode:transform(inAppCurrencyISOCode)];
#endif
    }

    void DevToDev::SocialNetworkConnect(const std::string& name)
    {
#if PLATFORM_IOS
        return [::DevToDev socialNetworkConnect:[SocialNetwork Custom:transform(name)]];
#endif
    }

    void DevToDev::SocialNetworkPost(const std::string& name, const std::string& reason)
    {
#if PLATFORM_IOS
        return [::DevToDev socialNetworkPost:[SocialNetwork Custom:transform(name)] withReason:transform(reason)];
#endif
    }

    void DevToDev::Age(int age)
    {
#if PLATFORM_IOS
        return [::DevToDev age:age];
#endif
    }

    void DevToDev::Gender(DTDGender gender)
    {
#if PLATFORM_IOS
        return [::DevToDev gender:gender == DTDUnknown ? Unknown : (gender == DTDMale ? Male : Female)];
#endif
    }

    void DevToDev::Cheater(bool cheater)
    {
#if PLATFORM_IOS
        return [::DevToDev cheater:transform(cheater)];
#endif
    }

    void DevToDev::SetUserId(const std::string& name)
    {
#if PLATFORM_IOS
        [::DevToDev setUserId:transform(name)];
#endif
    }

    void DevToDev::ReplaceUserId(const std::string& from, const std::string& to)
    {
#if PLATFORM_IOS
        return [::DevToDev replaceUserId:transform(from) to:transform(to)];
#endif
    }

    const char * DevToDev::GetUserId()
    {
#if PLATFORM_IOS
        return transform([::DevToDev getUserId]);
#endif

        return 0;
    }

    ///////////////////////
    // Push Manager
    ///////////////////////

    void DevToDevPushManager::SetDelegate()
    {
#if PLATFORM_IOS
        [[::DevToDevPushManager pushManager] setDelegate:[DevToDevUE4 sharedInstance]];
#endif
    }
}

#if PLATFORM_IOS
@interface DevToDevUE4() <DevToDevPushManagerDelegate>

@end

@implementation DevToDevUE4

+(id) sharedInstance {
    static DevToDevUE4 *sharedInstance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedInstance = [[DevToDevUE4 alloc] init];
    });
    return sharedInstance;
}

-(void) didRegisterForRemoteNotificationsWithDeviceToken: (NSString *) deviceToken {
    
}

-(void) didFailToRegisterForRemoteNotificationsWithError: (NSError *) error {

}

-(void) didReceiveRemoteNotification: (NSDictionary *) notification {

}
@end
#endif
