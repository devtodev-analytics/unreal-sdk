// Copyright 2018-2019 devtodev. All Rights Reserved.

#include "MessagingIOSImplementation.h"
#include "ConfigCacheIni.h"
#include "IOSTransformations.h"

#import <devtodev/devtodev.h>

using namespace devtodev;

DEFINE_LOG_CATEGORY_STATIC(LogDevToDevAnalytics, Log, All);

MessagingIOSImplementation::MessagingIOSImplementation(): DTDMessagingImplementation() {
    notificationOptions =
        Alert |
        Badge |
        Sound |
        Provisional |
        ProvidesAppNotificationSettings;

    if (!GConfig) return;

    notificationOptions = 0;

    
    bool badgeOptionEnabled = false;
    if (!GConfig->GetBool(TEXT("/Script/DevToDevEditor.DevToDevProjectSettings"), TEXT("Badge"), badgeOptionEnabled, GEngineIni) || badgeOptionEnabled) {
        notificationOptions |= Badge;
    }

    bool soundOptionEnabled = false;
    if (!GConfig->GetBool(TEXT("/Script/DevToDevEditor.DevToDevProjectSettings"), TEXT("Sound"), soundOptionEnabled, GEngineIni) || soundOptionEnabled) {
        notificationOptions |= Sound;
    }

    bool alertOptionEnabled = false;
    if (!GConfig->GetBool(TEXT("/Script/DevToDevEditor.DevToDevProjectSettings"), TEXT("Alert"), alertOptionEnabled, GEngineIni) || alertOptionEnabled) {
        notificationOptions |= Alert;
    }

    bool carPlayOptionEnabled = false;
    if (!GConfig->GetBool(TEXT("/Script/DevToDevEditor.DevToDevProjectSettings"), TEXT("CarPlay"), carPlayOptionEnabled, GEngineIni) || carPlayOptionEnabled) {
        notificationOptions |= CarPlay;
    }

    bool criticalAlertOptionEnabled = false;
    if (!GConfig->GetBool(TEXT("/Script/DevToDevEditor.DevToDevProjectSettings"), TEXT("CriticalAlert"), criticalAlertOptionEnabled, GEngineIni) || criticalAlertOptionEnabled) {
        notificationOptions |= CriticalAlert;
    }

    bool settingsOptionEnabled = false;
    if (!GConfig->GetBool(TEXT("/Script/DevToDevEditor.DevToDevProjectSettings"), TEXT("ProvidesAppNotificationSettings"), settingsOptionEnabled, GEngineIni) || settingsOptionEnabled) {
        notificationOptions |= ProvidesAppNotificationSettings;
    }

    bool provisionalOptionEnabled = false;
    if (!GConfig->GetBool(TEXT("/Script/DevToDevEditor.DevToDevProjectSettings"), TEXT("Provisional"), provisionalOptionEnabled, GEngineIni) || provisionalOptionEnabled) {
        notificationOptions |= Provisional;
    }
}

MessagingIOSImplementation::~MessagingIOSImplementation() {
    
}

void MessagingIOSImplementation::setPushNotificationsEnabled(bool isEnabled) {
    UE_LOG(LogDevToDevAnalytics, Warning, TEXT("NOTIFICATION OPTIONS %d"), notificationOptions);
    id pushManager = [::DevToDev pushManager];
    [pushManager setPushNotificationsOptions: notificationOptions];
    [pushManager setPushNotificationsEnabled: transform(isEnabled)];
    [pushManager setDelegate:(NSObject<DevToDevPushManagerDelegate> *)[UIApplication sharedApplication]];
}
