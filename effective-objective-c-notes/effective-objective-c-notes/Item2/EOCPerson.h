
#import <Foundation/Foundation.h>

@class EOCEmployer; // Forward declaring

@interface EOCPerson : NSObject

@property (nonatomic, copy) NSString *firstName;
@property (nonatomic, copy) NSString *lastName;
@property (nonatomic, strong) EOCEmployer *employer;
    
@end
