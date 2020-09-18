// Copyright 2018-2019 devtodev. All Rights Reserved.

#ifndef DTDMessagingImplementation_h
#define DTDMessagingImplementation_h

namespace devtodev {
    class DTDMessagingImplementation {
      public:
        DTDMessagingImplementation();
        virtual ~DTDMessagingImplementation();

        virtual void setPushNotificationsEnabled(bool isEnabled);
    };
} // namespace devtodev

#endif /* DTDMessagingImplementation_h */
