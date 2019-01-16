// Copyright 2018-2019 devtodev. All Rights Reserved.

#ifndef MessagingAndroidImplementation_h
#define MessagingAndroidImplementation_h

#include "../../Messaging/DTDMessagingImplementation.h"

namespace devtodev {
    class MessagingAndroidImplementation : public DTDMessagingImplementation {
      public:
        MessagingAndroidImplementation();
        virtual ~MessagingAndroidImplementation();

        virtual void setPushNotificationsEnabled(bool isEnabled);
    };
} // namespace devtodev

#endif /* MessagingAndroidImplementation_h */
