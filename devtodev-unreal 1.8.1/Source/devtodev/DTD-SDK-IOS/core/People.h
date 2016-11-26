//
//  People.h
//  devtodev
//
//  Created by Aleksey Kornienko on 07/04/16.
//  Copyright © 2016 devtodev. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Gender.h"

@interface People : NSObject

@property (nonatomic, retain) NSString * name;
@property (nonatomic, retain) NSString * email;
@property (nonatomic, retain) NSString * phone;
@property (nonatomic, retain) NSString * photo;
@property (nonatomic) DTDGender gender;
@property (nonatomic) NSInteger age;
@property (nonatomic) BOOL cheater;

-(void) setUserDataWithKey: (NSString *) key andValue: (id) value;

-(void) setUserData: (NSDictionary *) userData;

-(void) unsetUserDataWithKey: (NSString *) key;

-(void) unsetUserData: (NSArray *) keys;

-(void) clearUserData;

-(void) appendWithKey: (NSString *) key andValue: (id) value;

-(void) append: (NSDictionary *) userData;

-(void) unionWithKey: (NSString *) key andValue: (id) value;

-(void) unionWithData: (NSDictionary *) userData;

-(void) incrementWithKey: (NSString *) key andValue: (id) value;

-(void) increment: (NSDictionary *) values;

@end