// Copyright 2018-2019 devtodev. All Rights Reserved.

#ifndef PeopleAndroidImplementation_h
#define PeopleAndroidImplementation_h

#include "../../Analytics/DTDPeopleImplementation.h"

namespace devtodev {
    class PeopleAndroidImplementation : public DTDPeopleImplementation {
      public:
        explicit PeopleAndroidImplementation();
        virtual ~PeopleAndroidImplementation();

        virtual void cheater(bool cheater);

        virtual void age(int age);

        virtual void gender(DTDGender gender);

        virtual void email(const std::string& email);

        virtual void phone(const std::string& phone);

        virtual void photo(const std::string& photo);

        virtual void name(const std::string& photo);

        virtual void setUserData(const std::map<std::string, std::string>& Attributes);

        virtual void unsetUserData(const std::vector<std::string>& Attributes);

        virtual void clearUserData();

        virtual void incrementUserData(const std::map<std::string, int>& Attributes);

        virtual void appendUserData(const std::map<std::string, std::string>& Attributes);

        virtual void unionUserData(const std::map<std::string, std::string>& Attributes);
    };
}

#endif /* PeopleAndroidImplementation_h */
