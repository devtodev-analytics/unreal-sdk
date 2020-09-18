// Copyright 2018-2019 devtodev. All Rights Reserved.

#include "PeopleAndroidImplementation.h"
#include "DevToDevJNI.h"

using namespace devtodev;
using namespace std;

PeopleAndroidImplementation::PeopleAndroidImplementation() : DTDPeopleImplementation() {
}

PeopleAndroidImplementation::~PeopleAndroidImplementation() {
}

void PeopleAndroidImplementation::cheater(bool cheater) {
    jni_people_cheater(cheater);
}

void PeopleAndroidImplementation::age(int age) {
    jni_people_age(age);
}

void PeopleAndroidImplementation::gender(DTDGender gender) {
    jni_people_gender(gender);
}

void PeopleAndroidImplementation::email(const string& email) {
    jni_people_email(email);
}

void PeopleAndroidImplementation::phone(const string& phone) {
    jni_people_phone(phone);
}

void PeopleAndroidImplementation::photo(const string& photo) {
    jni_people_photo(photo);
}

void PeopleAndroidImplementation::name(const string& name) {
    jni_people_name(name);
}

void PeopleAndroidImplementation::setUserData(const map<string, string>& Attributes) {
    jni_people_setUserData(Attributes);
}

void PeopleAndroidImplementation::unsetUserData(const vector<string>& Attributes) {
    jni_people_unsetUserData(Attributes);
}

void PeopleAndroidImplementation::clearUserData() {
    jni_people_clearUserData();
}

void PeopleAndroidImplementation::incrementUserData(const map<string, int>& Attributes) {
    jni_people_incrementUserData(Attributes);
}

void PeopleAndroidImplementation::appendUserData(const map<string, string>& Attributes) {
    jni_people_appendUserData(Attributes);
}

void PeopleAndroidImplementation::unionUserData(const map<string, string>& Attributes) {
    jni_people_unionUserData(Attributes);
}
