#include "DevToDevPrivatePCH.h"

#include "DevToDevPushiOS.h"

#if PLATFORM_IOS

#import <devtodev/devtodev.h>
#include "DTDPushDelegateProxy.h"

@implementation UIApplication(DevToDevPushManagerDelegate)

- (NSObject<DevToDevPushManagerDelegate> *)getDevToDevPushDelegate {
	return (NSObject<DevToDevPushManagerDelegate> *)[UIApplication sharedApplication];
}

-(void) didRegisterForRemoteNotificationsWithDeviceToken: (NSString *) deviceToken
{
	const FString fToken = FString(UTF8_TO_TCHAR([deviceToken UTF8String]));
	[[DTDPushDelegateProxy sharedProxy] onDidRegisterForRemoteNotificationsWithDeviceToken:deviceToken];
}

-(void) didFailToRegisterForRemoteNotificationsWithError: (NSError *) error
{
	[[DTDPushDelegateProxy sharedProxy] onDidFailToRegisterForRemoteNotificationsWithError:error];
}

-(void) didReceiveRemoteNotification: (NSDictionary *) notification
{
	[[DTDPushDelegateProxy sharedProxy] onDidReceiveRemoteNotification:notification];
}

-(void) didOpenRemoteNotification: (DTDPushMessage *) pushMessage withAction: (DTDActionButton *) actionButton 
{
	[[DTDPushDelegateProxy sharedProxy] onDidOpenRemoteNotification:pushMessage withAction:actionButton];
}

@end

DevToDevPushiOS::DevToDevPushiOS()
{

}

void DevToDevPushiOS::Initialize()
{
	DTDPushImpl::Initialize();
}

#endif
