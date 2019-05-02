# Effective Objective-C Notes

[Effective Objective-C 2.0](https://www.effectiveobjectivec.com/) 的一点笔记。

## Chapter 1. Accustoming Yourself to Objective-C

### Item 1: Familiarize Yourself with Objective-C's Root

ObjC 的方法调用是运行时决定的，C的函数调用是编译时刻决定的。

ObjC 的对象(继承自NSObject)不能静态分配，比如分配在栈上。下面的代码无法编译：

    NSString s; // this will cause compile error

必须使用指针：

    NSString* s = @"Foobar";

如果是纯C的结构，还是可以在栈上分配:

    struct CGRect {
        CGPoint origin;
        CGSize size;
    };
    typedef CGRect CGRect;

    CGRect frame;   // ok.

### Item 2: Minimize Importing Headers in Headers

使用前向声明减少import，避免循环依赖：

    // EOCPerson.h
    #import <Foundation/Foundation.h>

    @class EOCEmployer; // Forward declaring

    @interface EOCPerson : NSObject
    @property (nonatomic, copy) NSString *firstName;
    @property (nonatomic, copy) NSString *lastName;
    @property (nonatomic, strong) EOCEmployer *employer;
    @end

    // EOCPerson.m
    #import "EOCPerson.h"
    #import "EOCEmployer.h"

    @implementation EOCPerson
    // Implementation of methods
    @end

如果需要类型的完整定义，比如要实现一个protocol，就必须使用import而不是前行声明：

    // Importing a header with a protocol in it
    // EOCRectangle.h
    #import "EOCShape.h"
    #import "EOCDrawable.h"

    @interface EOCRectangle : EOCShape <EOCDrawable>
    @property (nonatomic, assign) float width;
    @property (nonatomic, assign) float height;
    @end

### Item 3: Prefer Literal Syntax over the Equivalent Methods

使用 `@` （语法糖）来创建对象，让代码更易读：

    NSString *someString = @"Effective Objective-C 2.0";

    NSNumber *someNumber = [NSNumber numberWithInt:1];
    NSNumber *someNumber = @1;

    NSNumber *intNumber = @1;
    NSNumber *floatNumber = @2.5f;
    NSNumber *doubleNumber = @3.14159;
    NSNumber *boolNumber = @YES;
    NSNumber *charNumber = @‘a’;

数组：

    NSArray *animals = [NSArray arrayWithObjects:@"cat", @"dog", @"mouse", @"badger", nil];
    NSArray *animals = @[@"cat", @"dog", @"mouse", @"badger"];

    [mutableArray replaceObjectAtIndex:1 withObject:@"dog"];
    [mutableDictionary setObject:@"Galloway" forKey:@"lastName"];
    mutableArray[1] = @"dog";
    mutableDictionary[@"lastName"] = @"Galloway";

    NSMutableArray *mutable = [@[@1, @2, @3, @4, @5] mutableCopy];

注意，这里有一个不一致的行为：数组中如果对象有`nil`，`arrayWithObjects`会把当成结束标识，忽略后面的元素，而`@`会产生异常。

    NSArray *arrayA = [NSArray arrayWithObjects:object1, object2, object3, nil];
    NSArray *arrayB = @[object1, object2, object3];

如果`object2`为`nil`，`arrayA`的结果为`[ object1 ]`，而`arrayB`会扔出异常。

字典：

    NSDictionary *personData =
        [NSDictionary dictionaryWithObjectsAndKeys:
            @"Matt", @"firstName",
            @"Galloway", @"lastName",
            [NSNumber numberWithInt:28], @"age",
            nil];
    NSDictionary *personData =
        @{@"firstName" : @"Matt",
        @"lastName" : @"Galloway",
        @"age" : @28};

    NSString *lastName = [personData objectForKey:@"lastName"];
    NSString *lastName = personData[@"lastName"];

### Item 4: Prefer Typed Constants to Preprocessor #define

常量定义保存了类型信息，而 `#define` 没有类型信息，在预编期间就被直接替换了。

    // EOCAnimatedView.m
    #import "EOCAnimatedView.h"

    static const NSTimeInterval kAnimationDuration = 0.3;

    @implementation EOCAnimatedView
    - (void)animate {
        [UIView animateWithDuration:kAnimationDuration
                        animations:^(){
                            // Perform animations
                        }];
    }
    @end

在头文件里使用 `extern` 声明全局变量，在 `.m` 文件里赋值：

    // In the header file
    extern NSString *const StringConstant;

    // In the implementation file
    NSString *const StringConstant = @"VALUE";

### Item 5: Use Enumerations for States, Options, and Status Codes

和C语言一样，枚举的值可以自定义，而且枚举可以当整数用：

    enum EOCMethodOptions {
        EOCMethodOptionOne   = 1 << 0,
        EOCMethodOptionTwo   = 1 << 1,
        EOCMethodOptionThree = 1 << 2,
    };

    enum EOCMethodOptions options = EOCMethodOptionOne | EOCMethodOptionThree;
    if (options & OptionOne) {
        // OptionOne is set
    }

使用 NS_ENUM 和 NS_OPTIONS 宏来定义枚举：

    typedef NS_ENUM(NSUInteger, EOCConnectionState) {
        EOCConnectionStateDisconnected,
        EOCConnectionStateConnecting,
        EOCConnectionStateConnected,
    };
    typedef NS_OPTIONS(NSUInteger, EOCMethodOptions) {
        EOCMethodOptionOne = 1 << 0,
        EOCMethodOptionTwo = 1 << 1,
        EOCMethodOptionThree = 1 << 2,
    };

    typedef enum EOCConnectionState : NSUInteger EOCConnectionState;
    enum EOCConnectionState : NSUInteger {
        EOCConnectionStateDisconnected,
        EOCConnectionStateConnecting,
        EOCConnectionStateConnected,
    };

    typedef enum EOCMethodOptions : int EOCMethodOptions;
    enum EOCMethodOptions : int {
        EOCMethodOptionOne = 1 << 0,
        EOCMethodOptionTwo = 1 << 1,
        EOCMethodOptionThree = 1 << 2,
    };

    EOCMethodOptions options = EOCMethodOptionOne | EOCMethodOptionTwo;

## Chapter 2. Objects, Messaging, and the Runtime

### Item 6: Understand Properties

### Item 7: Access Instance Variables Primarily Directly When Accessing Them Internally

### Item 8: Understand Object Equality

### Item 9: Use the Class Cluster Pattern to Hide Implementation Detail

### Item 10: Use Associated Objects to Attach Custom Data to Existing Classes

### Item 11: Understand the Role of objc_msgSend

### Item 12: Understand Message Forwarding

### Item 13: Consider Method Swizzling to Debug Opaque Methods

### Item 14: Understand What a Class Object Is

## Chapter 3. Interface and API Design

### Item 15: Use Prefix Names to Avoid Namespace Clashes

### Item 16: Have a Designated Initializer

### Item 17: Implement the description Method

### Item 18: Prefer Immutable Objects

### Item 19: Use Clear and Consistent Naming

### Item 20: Prefix Private Method Names

### Item 21: Understand the Objective-C Error Model

### Item 22: Understand the NSCopying Protocol

## Chapter 4. Protocols and Categories

### Item 23: Use Delegate and Data Source Protocols for Interobject Communication

### Item 24: Use Categories to Break Class Implementations into Manageable Segments

### Item 25: Always Prefix Category Names on Third-Party Classes

### Item 26: Avoid Properties in Categories

### Item 27: Use the Class-Continuation Category to Hide Implementation Detail

### Item 28: Use a Protocol to Provide Anonymous Objects

## Chapter 5. Memory Management

### Item 29: Understand Reference Counting

### Item 30: Use ARC to Make Reference Counting Easier

### Item 31: Release References and Clean Up Observation State Only in dealloc

### Item 32: Beware of Memory Management with Exception-Safe Code

### Item 33: Use Weak References to Avoid Retain Cycles

### Item 34: Use Autorelease Pool Blocks to Reduce High-Memory Waterline

### Item 35: Use Zombies to Help Debug Memory-Management Problems

### Item 36: Avoid Using retainCount

## Chapter 6. Blocks and Grand Central Dispatch

### Item 37: Understand Blocks

### Item 38: Create typedefs for Common Block Types

### Item 39: Use Handler Blocks to Reduce Code Separation

### Item 40: Avoid Retain Cycles Introduced by Blocks Referencing the Object Owning Them

### Item 41: Prefer Dispatch Queues to Locks for Synchronization

### Item 42: Prefer GCD to performSelector and Friends

### Item 43: Know When to Use GCD and When to Use Operation Queues

### Item 44: Use Dispatch Groups to Take Advantage of Platform Scaling

### Item 45: Use dispatch_once for Thread-Safe Single-Time Code Execution

### Item 46: Avoid dispatch_get_current_queue

## Chapter 7. The System Frameworks

### Item 47: Familiarize Yourself with the System Frameworks

### Item 48: Prefer Block Enumeration to for Loops

### Item 49: Use Toll-Free Bridging for Collections with Custom Memory-Management Semantics

### Item 50: Use NSCache Instead of NSDictionary for Caches

### Item 51: Keep initialize and load Implementations Lean

### Item 52: Remember that NSTimer Retains Its Target

## References

* https://www.effectiveobjectivec.com
* https://github.com/effectiveobjc/code
