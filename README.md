# Effective Objective-C Notes

[Effective Objective-C 2.0](https://www.effectiveobjectivec.com/) 的一点笔记。

## Chapter 1 Accustoming Yourself to Objective-C

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

## References

* https://www.effectiveobjectivec.com
* https://github.com/effectiveobjc/code
