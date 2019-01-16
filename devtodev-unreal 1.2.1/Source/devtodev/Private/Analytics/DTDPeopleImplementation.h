// Copyright 2018-2019 devtodev. All Rights Reserved.

#ifndef DTDPeopleImplementation_hpp
#define DTDPeopleImplementation_hpp

#include <map>
#include <string>
#include <vector>

namespace devtodev {
    enum DTDGender { DTDUnknown = 0, DTDMale = 1, DTDFemale = 2 };

    class DTDPeopleImplementation {
      public:
        explicit DTDPeopleImplementation();
        virtual ~DTDPeopleImplementation(){};

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
} // namespace devtodev

#endif /* DTDPeopleImplementation_hpp */
