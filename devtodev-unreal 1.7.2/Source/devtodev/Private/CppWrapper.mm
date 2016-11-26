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
    
    NSMutableArray* transform(const std::vector<std::string>& a)
    {
        NSMutableArray * array = [[NSMutableArray alloc] init];
        for (std::string str : a)
        {
            [array addObject:transform(str)];
        }
        
        return array;
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
    
    NSMutableDictionary* transform(const std::map<std::string, std::string>& Attributes)
    {
        NSMutableDictionary * params = [[NSMutableDictionary alloc] init];
        NSString *key;
        NSString *value;
        long iValue;
        double dValue;
        for (auto pair : Attributes) {
            key = transform(pair.first);
            value = transform(pair.second);
            
            iValue = [value integerValue];
            dValue = [value doubleValue];
            
            if (iValue == 0 && dValue == 0 && ![value isEqualToString:@"0"]) {
                [params setObject:value forKey:key];
            } else if (dValue > iValue) {
                [params setObject:[NSNumber numberWithDouble:dValue] forKey:key];
            } else {
                [params setObject:[NSNumber numberWithInteger:iValue] forKey:key];
            }
        }
        return params;
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
    
    void DevToDev::Referrer(const std::map<std::string, std::string>& entries)
    {
#if PLATFORM_IOS
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
    
    People DevToDev::ActivePeople()
    {
        static People p;
        return p;
    }

    /////////////////////////////////
    // User Data
    /////////////////////////////////

    void People::Cheater(bool cheater)
    {
#if PLATFORM_IOS
        id people = [::DevToDev activeUser];
        [people setCheater:transform(cheater)];
#endif
    }

    void People::Age(int age)
    {
#if PLATFORM_IOS
        id people = [::DevToDev activeUser];
        [people setAge:age];
#endif
    }

    void People::Gender(DTDGender dtdGender)
    {
#if PLATFORM_IOS
        id people = [::DevToDev activeUser];
        [people setGender:dtdGender == DTDUnknown ? Unknown : (dtdGender == DTDMale ? Male : Female)];
#endif
    }

    void People::Email(const std::string& email)
    {
#if PLATFORM_IOS
        id people = [::DevToDev activeUser];
        [people setEmail:transform(email)];
#endif
    }

    void People::Phone(const std::string& phone)
    {
#if PLATFORM_IOS
        id people = [::DevToDev activeUser];
        [people setPhone:transform(phone)];
#endif
    }

    void People::Photo(const std::string& photo)
    {
#if PLATFORM_IOS
        id people = [::DevToDev activeUser];
        [people setPhoto:transform(photo)];
#endif
    }
    
    void People::Name(const std::string& name)
    {
#if PLATFORM_IOS
        id people = [::DevToDev activeUser];
        [people setName:transform(name)];
#endif
    }

    void People::SetUserData(const std::map<std::string, std::string>& Attributes)
    {
#if PLATFORM_IOS
        id people = [::DevToDev activeUser];
        NSMutableDictionary* params = transform(Attributes);
        [people setUserData:params];
#endif
    }

    void People::UnsetUserData(const std::vector<std::string>& Attributes)
    {
#if PLATFORM_IOS
        id people = [::DevToDev activeUser];
        NSMutableArray* params = transform(Attributes);
        [people unsetUserData:params];
#endif
    }

    void People::ClearUserData()
    {
#if PLATFORM_IOS
        id people = [::DevToDev activeUser];
        [people clearUserData];
#endif
    }

    void People::IncrementUserData(const std::map<std::string, std::string>& Attributes)
    {
#if PLATFORM_IOS
        id people = [::DevToDev activeUser];
        NSMutableDictionary* params = transform(Attributes);
        [people increment:params];
#endif
    }

    void People::AppendUserData(const std::map<std::string, std::string>& Attributes)
    {
#if PLATFORM_IOS
        id people = [::DevToDev activeUser];
        NSMutableDictionary* params = transform(Attributes);
        [people append:params];
#endif
    }

    void People::UnionUserData(const std::map<std::string, std::string>& Attributes)
    {
#if PLATFORM_IOS
        id people = [::DevToDev activeUser];
        NSMutableDictionary* params = transform(Attributes);
        [people unionWithData:params];
#endif
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
