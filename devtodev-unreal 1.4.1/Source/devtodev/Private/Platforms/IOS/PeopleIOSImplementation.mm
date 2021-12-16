// Copyright 2018-2019 devtodev. All Rights Reserved.

#include "PeopleIOSImplementation.h"

#import <devtodev/devtodev.h>

#include "IOSTransformations.h"

using namespace std;
using namespace devtodev;

PeopleIOSImplementation::PeopleIOSImplementation(): DTDPeopleImplementation() {
    
}

PeopleIOSImplementation::~PeopleIOSImplementation() {
    
}

void PeopleIOSImplementation::cheater(bool cheater) {
    id people = [::DevToDev activeUser];
    [people setCheater:transform(cheater)];
}

void PeopleIOSImplementation::age(int age) {
    id people = [::DevToDev activeUser];
    [people setAge:age];
}

void PeopleIOSImplementation::gender(DTDGender gender) {
    id people = [::DevToDev activeUser];
    [people setGender:gender == DTDUnknown ? Unknown : (gender == DTDMale ? Male : Female)];
}

void PeopleIOSImplementation::email(const string& email) {
    id people = [::DevToDev activeUser];
    [people setEmail:transform(email)];
}

void PeopleIOSImplementation::phone(const string& phone) {
    id people = [::DevToDev activeUser];
    [people setPhone:transform(phone)];
}

void PeopleIOSImplementation::photo(const string& photo) {
    id people = [::DevToDev activeUser];
    [people setPhoto:transform(photo)];
}

void PeopleIOSImplementation::name(const string& name) {
    id people = [::DevToDev activeUser];
    [people setName:transform(name)];
}

void PeopleIOSImplementation::setUserData(const map<string, string>& Attributes) {
    id people = [::DevToDev activeUser];
    NSMutableDictionary* params = transform(Attributes);
    [people setUserData:params];
}

void PeopleIOSImplementation::unsetUserData(const vector<string>& Attributes) {
    id people = [::DevToDev activeUser];
    NSMutableArray* params = transform(Attributes);
    [people unsetUserData:params];
}

void PeopleIOSImplementation::clearUserData() {
    id people = [::DevToDev activeUser];
    [people clearUserData];
}

void PeopleIOSImplementation::incrementUserData(const map<string, int>& Attributes) {
    id people = [::DevToDev activeUser];
    NSMutableDictionary* params = transform(Attributes);
    [people increment:params];
}

void PeopleIOSImplementation::appendUserData(const map<string, string>& Attributes) {
    id people = [::DevToDev activeUser];
    NSMutableDictionary* params = transform(Attributes);
    [people append:params];
}

void PeopleIOSImplementation::unionUserData(const map<string, string>& Attributes) {
    id people = [::DevToDev activeUser];
    NSMutableDictionary* params = transform(Attributes);
    [people unionWithData:params];
}
