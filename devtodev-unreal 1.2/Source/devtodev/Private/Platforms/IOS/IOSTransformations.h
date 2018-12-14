#ifndef IOSTransformations_h
#define IOSTransformations_h

#include <map>
#include <string>
#include <vector>

#import <Foundation/Foundation.h>
#import <devtodev/devtodev.h>

BOOL transform(bool b);
NSInteger transform(int i);
NSNumber* transform(float v);
NSNumber* transform(double v);
const char* transform(NSString* s);
NSString* transform(const std::string& s);
NSMutableArray* transform(const std::vector<std::string>& a);
NSMutableDictionary* transform(const std::map<std::string, int>& m);
NSMutableDictionary* transform(const std::map<std::string, std::string>& Attributes);
LocationEventParams* transformLocationEventParams(const std::map<std::string, std::string>& Attributes, const std::map<std::string, std::string>& Earned,
                                                  const std::map<std::string, std::string>& Spent);

#endif /* IOSTransformations_h */
