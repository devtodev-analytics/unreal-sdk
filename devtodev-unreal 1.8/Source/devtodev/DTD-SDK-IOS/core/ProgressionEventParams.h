#import <Foundation/Foundation.h>

@interface ProgressionEventParams : NSObject <NSCoding>

@property (nonatomic, retain) NSMutableDictionary * earned;
@property (nonatomic, retain) NSMutableDictionary * spent;
@property (nonatomic) BOOL isSuccess;

- (void) mergeWithParameters: (ProgressionEventParams *) parameters;

- (NSMutableDictionary *) dictionary;

@end
