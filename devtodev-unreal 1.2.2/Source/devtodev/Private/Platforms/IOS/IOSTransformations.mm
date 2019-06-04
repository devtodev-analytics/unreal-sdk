// Copyright 2018-2019 devtodev. All Rights Reserved.

#include "IOSTransformations.h"

/////////////////////////
// Obj-c to C++
/////////////////////////

const char * transform(NSString * s) {
    return [s cStringUsingEncoding:NSUTF8StringEncoding];
}

/////////////////////////
// C++ to Obj-C
/////////////////////////
BOOL transform(bool b) {
    return b ? YES : NO;
}

NSInteger transform(int i) {
    return NSInteger(i);
}

NSNumber* transform(float v) {
    return [NSNumber numberWithFloat:v];
}

NSNumber* transform(double v) {
    return [NSNumber numberWithDouble:v];
}

NSString* transform(const std::string& s) {
    return [NSString stringWithUTF8String:s.c_str()];
}

NSMutableArray* transform(const std::vector<std::string>& a) {
    NSMutableArray * array = [[NSMutableArray alloc] init];
    for (std::string str : a) {
        [array addObject:transform(str)];
    }
    
    return array;
}

NSMutableDictionary* transform(const std::map<std::string, int>& m) {
    NSMutableDictionary* dict = [[NSMutableDictionary alloc] init];
    
    for (auto pair : m) {
        [dict setObject:[NSNumber numberWithInt:pair.second] forKey:transform(pair.first)];
    }
    
    return dict;
}

NSMutableDictionary* transform(const std::map<std::string, std::string>& Attributes) {
    NSMutableDictionary * params = [[NSMutableDictionary alloc] init];
    NSString *key;
    NSString *value;
    long iValue;
    double dValue;
    for (auto pair : Attributes) {
        key = transform(pair.first);
        value = transform(pair.second);
        
        iValue = [value integerValue];
        dValue = [value doubleValue];
        
        if (iValue == 0 && dValue == 0 && ![value isEqualToString:@"0"]) {
            [params setObject:value forKey:key];
        } else if (dValue > iValue) {
            [params setObject:[NSNumber numberWithDouble:dValue] forKey:key];
        } else {
            [params setObject:[NSNumber numberWithInteger:iValue] forKey:key];
        }
    }
    return params;
}

LocationEventParams* transformLocationEventParams(const std::map<std::string, std::string>& Attributes, const std::map<std::string, std::string>& Earned, const std::map<std::string, std::string>& Spent) {
    LocationEventParams * params = [[LocationEventParams alloc] init];
    NSString *key;
    NSString *value;
    
    NSNumberFormatter * formatter = [[NSNumberFormatter alloc] init];
    formatter.numberStyle = NSNumberFormatterDecimalStyle;
    
    for (auto pair : Attributes) {
        key = transform(pair.first);
        value = transform(pair.second);
        
        if ([key isEqualToString:@"difficulty"]) {
            [params setDifficulty:value.integerValue];
        } else if ([key isEqualToString:@"source"]) {
            [params setSource:value];
        } else if ([key isEqualToString:@"success"]) {
            BOOL isSuccess = ([value isEqualToString:@"true"] || [value isEqualToString:@"1"]) ? YES : NO;
            [params setIsSuccess: isSuccess];
        } else if ([key isEqualToString:@"duration"]) {
            NSNumber * number = [formatter numberFromString:value];
            if (number) {
                [params setDuration:number];
            }
        }
    }
    
    NSMutableDictionary * earnedDictionary = [[NSMutableDictionary alloc] init];
    for (auto pair : Earned) {
        key = transform(pair.first);
        value = transform(pair.second);
        NSNumber * number = [formatter numberFromString:value];
        if (number) {
            [earnedDictionary setObject:number forKey:key];
        }
    }
    [params setEarned: earnedDictionary];
    
    NSMutableDictionary * spentDictionary = [[NSMutableDictionary alloc] init];
    for (auto pair : Spent) {
        key = transform(pair.first);
        value = transform(pair.second);
        NSNumber * number = [formatter numberFromString:value];
        if (number) {
            [spentDictionary setObject:number forKey:key];
        }
    }
    [params setSpent: spentDictionary];
    
    return params;
}
