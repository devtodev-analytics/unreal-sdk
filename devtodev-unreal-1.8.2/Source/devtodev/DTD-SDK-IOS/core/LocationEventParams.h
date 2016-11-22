#import <Foundation/Foundation.h>
#import "ProgressionEventParams.h"

@interface LocationEventParams : ProgressionEventParams

@property (nonatomic) NSInteger difficulty;
@property (nonatomic, retain) NSString * source;
@property (nonatomic, retain) NSNumber * duration;

@end
