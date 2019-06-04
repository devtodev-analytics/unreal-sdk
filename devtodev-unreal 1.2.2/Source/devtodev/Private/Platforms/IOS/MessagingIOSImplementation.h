// Copyright 2018-2019 devtodev. All Rights Reserved.

#ifndef MessagingIOSImplementation_h
#define MessagingIOSImplementation_h

#include "../../Messaging/DTDMessagingImplementation.h"

namespace devtodev {
    enum DTDNotificationOptions {
        Badge = (1 << 0),
        Sound = (1 << 1),
        Alert = (1 << 2),
        CarPlay = (1 << 3),
        CriticalAlert = (1 << 4),
        ProvidesAppNotificationSettings = (1 << 5),
        Provisional = (1 << 6)
    };

    class MessagingIOSImplementation : public DTDMessagingImplementation {
      public:
        MessagingIOSImplementation();
        virtual ~MessagingIOSImplementation();

        virtual void setPushNotificationsEnabled(bool isEnabled);

      private:
        int notificationOptions;
    };
} // namespace devtodev

#endif /* MessagingIOSImplementation_h */
