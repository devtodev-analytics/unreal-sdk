#if PLATFORM_IOS

#import <devtodev/devtodev.h>

@interface DTDPushDelegateProxy : NSObject

+ (instancetype)sharedProxy;

- (void) onRegisterForPushNotifications;

- (void) onDidRegisterForRemoteNotificationsWithDeviceToken: (NSString *) deviceToken;

- (void) onDidFailToRegisterForRemoteNotificationsWithError: (NSError *) error;

- (void) onDidReceiveRemoteNotification: (NSDictionary *) notification;

- (void) onDidOpenRemoteNotification: (DTDPushMessage *) pushMessage withAction: (DTDActionButton *) actionButton;

@end

#endif