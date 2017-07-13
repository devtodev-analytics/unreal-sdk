#include "DevToDevPrivatePCH.h"

#import "DTDPushDelegateProxy.h"

#if PLATFORM_IOS

@interface DTDPushDelegateProxy()

@property (nonatomic, assign) BOOL listenersReady;
@property (atomic, assign) BOOL registeringForPushes;

@end


@implementation DTDPushDelegateProxy

+ (instancetype)sharedProxy
{
	static DTDPushDelegateProxy *instance = nil;
	static dispatch_once_t pred;
	
	dispatch_once(&pred, ^{
		instance = [DTDPushDelegateProxy new];
	});
	
	return instance;
}

- (void)onRegisterForPushNotifications
{
	self.registeringForPushes = YES;
}

- (void) onDidRegisterForRemoteNotificationsWithDeviceToken: (NSString *) deviceToken
{
	if (self.registeringForPushes)
	{
		const FString fToken = FString(UTF8_TO_TCHAR([deviceToken UTF8String]));
		FAnalyticsDevToDev::PushRegisterSuccess.Broadcast(fToken);
		
		self.registeringForPushes = NO;
	}
}

- (void) onDidFailToRegisterForRemoteNotificationsWithError: (NSError *) error
{
	if (self.registeringForPushes)
	{
		const FString fError = FString(UTF8_TO_TCHAR([error.description UTF8String]));
		FAnalyticsDevToDev::PushRegisterError.Broadcast(fError);
		
		self.registeringForPushes = NO;
	}
}


- (void) onDidReceiveRemoteNotification: (NSDictionary *) notification
{
	NSLog(@"onDidReceiveRemoteNotification");
	@synchronized (self)
	{
		NSError *error;
     	NSData *jsonData = [NSJSONSerialization dataWithJSONObject:notification options:0 error:&error];
     	NSString * jsonString = @"";
     	if (jsonData) {
        	jsonString = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
     	}

		[self dispatchPushReceive:jsonString];
	}
}

- (void) onDidOpenRemoteNotification: (DTDPushMessage *) pushMessage withAction: (DTDActionButton *) actionButton 
{
	NSLog(@"onDidOpenRemoteNotification %@ - %@", pushMessage, actionButton);
	@synchronized (self)
	{
		NSError *error;
     	NSData *jsonData = [NSJSONSerialization dataWithJSONObject:[pushMessage dictionary] options:0 error:&error];
     	NSString * jsonMessage = @"";
     	if (jsonData) {
     		NSLog(@"Message %@",[pushMessage dictionary]);
        	jsonMessage = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
     	}
     	NSString * jsonAction = @"";
     	if (actionButton) {
     		NSLog(@"Action %@", [actionButton dictionary]);
     		NSData *dataAction = [NSJSONSerialization dataWithJSONObject:[actionButton dictionary] options:0 error:&error];
     		if (dataAction) {
        		jsonAction = [[NSString alloc] initWithData:dataAction encoding:NSUTF8StringEncoding];
     		}
     	}
     	

		[self dispatchPushOpen:jsonMessage withActionButton:jsonAction];
	}
}

- (void) dispatchPushReceive: (NSString*) pushMessage
{
	const FString fPushMessage = FString(UTF8_TO_TCHAR([pushMessage UTF8String]));
	FAnalyticsDevToDev::PushReceived.Broadcast(fPushMessage);
}

- (void) dispatchPushOpen: (NSString *) pushMessage withActionButton: (NSString *) actionButton {
	const FString fPushMessage = FString(UTF8_TO_TCHAR([pushMessage UTF8String]));
	const FString fActionButton = FString(UTF8_TO_TCHAR([actionButton UTF8String]));
	FAnalyticsDevToDev::PushOpened.Broadcast(fPushMessage, fActionButton);
}

@end

#endif
