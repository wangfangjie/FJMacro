//
//  FoundationMacro.m
//  FJMacro
//
//  Created by wangfj on 2017/8/17.
//  Copyright © 2017年 FJMacro. All rights reserved.
//

#import "FoundationMacro.h"

@implementation FoundationMacro
//// 函数调用堆栈
//+(void)printBacktrace
//{
//    void *callstack[128] = {0};
//    int frameCount = backtrace(callstack, 128);
//    char **frameStrings = backtrace_symbols(callstack, frameCount);
//    if ( frameStrings != NULL ) {
//        // Start with frame 1 because frame 0 is PrintBacktrace()
//        for ( int i = 1; i < frameCount; i++ ) {
//            printf("%s\n", frameStrings[i]);
//
//        }
//        free(frameStrings);
//    }
//}


+(void)printFatherClass:(id)obj
{
#if DEBUG
    printf("\n class:");
    Class cls = object_getClass(obj);
    while (cls)
    {
        printf(" %s -->", class_getName(cls));
        cls = class_getSuperclass(cls);
    }
    printf("\n");
#endif
}


+(void)ios_dialPhone:(NSString *)phoneNumber needAlert:(BOOL)isNeedAlert
{
    if (phoneNumber.length > 0)
    {
        NSString *tel = [NSString stringWithFormat:(isNeedAlert ? @"telprompt://%@" : @"tel://%@"), phoneNumber];
        
        [[UIApplication sharedApplication] openURL:[NSURL URLWithString:tel]];
    }
}

/**
 计算代码执行时间的方法（相比其他方法要好一些）
 
 @param block 要执行的代码块
 
 @return 返回毫秒时间
 */
+(CGFloat)calculateRunTimeBlock:(void (^)(void))block
{
    mach_timebase_info_data_t info;
    if (mach_timebase_info(&info) != KERN_SUCCESS) return 0.0;
    
    uint64_t start = mach_absolute_time ();
    block();
    uint64_t end = mach_absolute_time ();
    uint64_t elapsed = end - start;
    
    uint64_t nanos = elapsed * info.numer / info.denom;//得到纳秒
    
    CGFloat nanoTime =(CGFloat)nanos / NSEC_PER_MSEC;
    
    LOG(@"%@=%.2fms",LANGUAGE_IS_EN()?@"CODE EXECUTE_TIME":@"代码执行时间",nanoTime);
    
    return nanoTime; //计算结果是毫秒
}

@end
