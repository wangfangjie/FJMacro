//
//  FoundationMacro.h
//  FJMacro
//
//  Created by wangfj on 2017/8/17.
//  Copyright © 2017年 FJMacro. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <objc/runtime.h>
#import <mach/mach_time.h>
//#import <execinfo.h>

//------------------weak strong reference----------------
//--------------------弱强引用---------------------------

//判断是不是支持arc模式
#if __has_feature(objc_arc)

#define WEAK_SELF          __weak __typeof(self) weakSelf = self;
#define WEAK(obj)          __weak __typeof(obj) weak##obj = obj;
#define STRONG_SELF        __strong __typeof(weakSelf)strongSelf = weakSelf;

#else

#define WEAK_SELF          __block __typeof(self) weakSelf = self;
#define WEAK(obj)          __block __typeof(obj) weak##obj = obj;
#define STRONG_SELF        __strong __typeof(weakSelf)strongSelf = weakSelf;

#endif


//--------------------Print log---------------------------
//--------------------打印日志---------------------------

#define STRING_FORMAT(fmt, ...)      [NSString stringWithFormat:(@"%z, %s(line %d) " fmt), clock(), __FUNCTION__, __LINE__, ##__VA_ARGS__]



#if DEBUG

#define LOG(...) NSLog(__VA_ARGS__);

#define LOG_FMT(fmt, ...) NSLog((@"%s (line %d) " fmt), __FUNCTION__, __LINE__, ##__VA_ARGS__);

#define LOG_IF(x, fmt, ...) if (x) {LOG_FMT(fmt, ##__VA_ARGS__);}

#define PRINTF(fmt, ...)  printf(("%ld, %s (line %d) " fmt), clock(), __FUNCTION__, __LINE__, ##__VA_ARGS__);

// 打印super class
#define PRINT_FATHERCLASS(obj) [FoundationMacro printFatherClass:obj];


#else


#define LOG(...)

#define LOG_FMT(fmt, ...)

#define LOG_IF(x, fmt, ...)

#define PRINTF(fmt, ...)

#define PRINT_FATHERCLASS(obj)


#endif


//--------------------assert---------------------------
//--------------------断言---------------------------

#if DEBUG


#define ASSERT(obj)               assert((obj))

#define ASSERT_CLASS(obj, cls)  ASSERT((x) && IS_KIND_OF(obj,cls))//断言实例有值和类型

// (assert main thread)断言在主线程中
#define ASSERT_MAIN_THREAD             ASSERT(IS_MAIN_THREAD)


#else


#define ASSERT(obj)

#define ASSERT_CLASS(obj, cls)

#define ASSERT_MAIN_THREAD


#endif



//------Code execution time(return min seconds）-------------
//------------------代码运算时间(返回毫秒时间)------------------

/*
 CGFloat time =  EXECUTE_TIME({
 sleep(2);
 });
 
 LOG(@"代码执行时间%fms",time);
 */
#define EXECUTE_TIME(block) [FoundationMacro calculateRunTimeBlock:^{(block);}];


//------------------Kind Of Class---------------------
//------------------类型判断---------------------------

// 判断实例类型(含父类)
#define IS_KIND_OF(obj, cls)                [(obj) isKindOfClass:[cls class]]

// 判断实例类型(不含父类)
#define IS_MEMBER_OF(x, cls)              [(x) isMemberOfClass:[cls class]]

// 判断实例类型(是否是子类)
#define IS_SUBCLASS_OF(x, cls)              [(x) isSubclassOfClass:[cls class]]


//--------------------Notification---------------------------
//--------------------通知---------------------------

#define __Noti  [NSNotificationCenter defaultCenter]

// 添加观察者
#define ADD_OBSERVER(__obj, __sel, __name, __message)      [__Noti addObserver:__obj selector:__sel name:__name object:__message]

// 发送消息（同步）
#define POST_NOTI(__name, __message)                 [__Noti postNotificationName:__name object:__message]

// 取消观察
#define REMOVE_SELF                     [__Noti removeObserver:self]

#define REMOVE(__obj)                    [__Noti removeObserver:__obj]

#define REMOVE_NAME(__obj, __name, __message)      [__Noti removeObserver:__obj name:__name object:__message]


//--------------------APP Version----------------------
//--------------------APP版本---------------------------

//获取APP版本
#ifndef APP_VERSION
#define APP_VERSION [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleShortVersionString"]

//获取APP的build版本
#define APP_BUILD_VERSION [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleVersion"]

#endif


//--------------------Thread------------------------
//--------------------线程---------------------------

// (is main thread)判断是否主线程
#define IS_MAIN_THREAD                [NSThread isMainThread]

// (run in main thread)使block在主线程中运行
#define RUN_MAIN_THREAD(block)    if (IS_MAIN_THREAD) {(block);} else {dispatch_async(dispatch_get_main_queue(), ^{(block);});}

// (run in global thread)使block在子线程中运行
#define RUN_GlOBAL_THREAD(block)    if (!IS_MAIN_THREAD) {(block);} else {dispatch_async(dispatch_get_global_queue(0,0), ^{(block);});}

// (safe run block)安全运行block
#define BLOCK(block, ...)     if (block) {block(__VA_ARGS__);}



//--------------------dial phone------------------------
//--------------------拨打电话---------------------------


/**
 Call the system call
 调用系统拨打电话
 
 @param phoneNumber 电话号码
 @param isNeedAlert 是否弹出alert询问
 
 */
#define DIAL_PHONE(phoneNumber,isNeedAlert) [FoundationMacro ios_dialPhone:phoneNumber needAlert:isNeedAlert]



//--------------------SandBox Path---------------------------
//--------------------沙盒路径---------------------------

//获取沙盒主目录路径
#define PATH_HOME NSHomeDirectory()

//沙盒文档路径
/*Documents 目录：您应该将所有应用程序数据文件写入到这个目录下。这个目录用于存储用户数据或其它应该定期备份的信息。
 ②是否会被iTunes同步
 是
 */
#define PATH_DOCUMENT     [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0]


//沙盒library路径
/*Library目录：这个目录下有两个子目录：Preference,Caches
 ①存放内容
 苹果建议用来存放默认设置或其它状态信息。该路径下的文件夹，除Caches以外，都会被iTunes备份。
 ②是否会被iTunes同步
 是，但是要除了Caches子目录外
 */
#define PATH_LIBRARY      [NSSearchPathForDirectoriesInDomains(NSLibraryDirectory, NSUserDomainMask, YES) objectAtIndex:0]


//沙盒Preference路径
/*①存放内容
 应用程序的偏好设置文件,配置目录，配置文件。我们使用NSUserDefaults写的设置数据都会保存到该目录下的一个plist文件中，这就是所谓的写到plist中！
 ②是否会被iTunes同步
 是
 */
#define PATH_PREFERENCE      [[NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES) objectAtIndex:0] stringByAppendingPathComponent:@"Preference"]


//沙盒Caches缓存路径
//Caches 目录：用于存放应用程序专用的支持文件，保存应用程序再次启动过程中需要的信息,存储项目缓存,常用设置。可创建子文件夹。可以用来放置您希望被备份但不希望被用户看到的数据。
/*①存放内容
 主要是缓存文件，用户使用过程中缓存都可以保存在这个目录中。前面说过，Documents目录用于保存不可再生的文件，那么这个目录就用于保存那些可再生的文件，比如网络请求的数据。鉴于此，应用程序通常还需要负责删除这些文件。
 ②是否会被iTunes同步
 否。
 */
#define PATH_CACHE      [NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES) objectAtIndex:0]

//沙盒tmp路径
//tmp 目录：这个目录用于存放临时文件，保存应用程序再次启动过程中不需要的信息。该路径下的文件不会被iTunes备份。
/*①存放内容
 各种临时文件，保存应用再次启动时不需要的文件。而且，当应用不再需要这些文件时应该主动将其删除，因为该目录下的东西随时有可能被系统清理掉，目前已知的一种可能清理的原因是系统磁盘存储空间不足的时候。
 ②是否会被iTunes同步
 否
 */
#define PATH_TMP      NSTemporaryDirectory()


//--------------------file---------------------------
//--------------------文件---------------------------

//判断文件是否存在
#define IS_FILE_EXIST(path)             [[NSFileManager defaultManager] fileExistsAtPath:(path)]


//--------------Reference counting----------------------
//--------------------引用计数---------------------------


#define MRC_Retain(x)           [(x) retain];
#define MRC_Copy(x)             [(x) copy];
#define MRC_Release(x)          {if(x){[(x) release];}}
#define MRC_Release_View(x)     {if(x){[(x) removeFromSuperview];[(x) release];(x)=nil;}}
#define MRC_Dealloc(x)          [(x) dealloc];


#define ARC_Retain(x)           (x)
#define ARC_Copy(x)             (x)
#define ARC_Release(x)          {(x)=nil;}
#define ARC_Release_View(x)     {if(x){[(x) removeFromSuperview];(x)=nil;}}
#define ARC_Dealloc(x)


//判断是不是支持arc模式
#if __has_feature(objc_arc)

#define OC_Retain(x)            ARC_Retain(x)
#define OC_Copy(x)              ARC_Copy(x)
#define OC_Release(x)           ARC_Release(x)
#define OC_Release_View(x)      ARC_Release_View(x)
#define OC_SuperDealloc

#else

#define OC_Retain(x)            MRC_Retain(x)
#define OC_Copy(x)              MRC_Copy(x)
#define OC_Release(x)           MRC_Release(x)
#define OC_Release_View(x)      MRC_Release_View(x)
#define OC_SuperDealloc         MRC_Dealloc(super)

#endif


//--------------------local Language---------------------------
//--------------------本地语言---------------------------

//判断本地语言是不是英语
#define LANGUAGE_IS_EN()         [[[NSLocale preferredLanguages] objectAtIndex:0] isEqualToString:@"en"]


//--------------------runtime---------------------------


//runtime换类方法
#define EXCHANGE_IMP_CLASS_METHOD(_cls_, _sel_1, _sel_2) {\
Method method1 = class_getClassMethod(_cls_, _sel_1);\
Method method2 = class_getClassMethod(_cls_, _sel_2);\
ASSERT(method1 != NULL);\
ASSERT(method2 != NULL);\
LOG(@"exchange [%@], +%@(0x%08lx) ==> +%@(0x%08lx), ", NSStringFromClass(_cls_), NSStringFromSelector(_sel_1), (long)method1, NSStringFromSelector(_sel_2), (long)method2);\
if (method1 && method2) {\
method_exchangeImplementations(method1, method2);\
}\
}

//runtime换实例方法
#define EXCHANGE_IMP_CLASS_INSTANCE(_cls_, _sel_1, _sel_2) {\
Method method1 = class_getInstanceMethod(_cls_, _sel_1);\
Method method2 = class_getInstanceMethod(_cls_, _sel_2);\
ASSERT(method1 != NULL);\
ASSERT(method2 != NULL);\
LOG(@"exchange (%@), -%@(0x%08lx) ==> -%@(0x%08lx), ", NSStringFromClass(_cls_), NSStringFromSelector(_sel_1), (long)method1, NSStringFromSelector(_sel_2), (long)method2);\
if (method1 && method2) {\
method_exchangeImplementations(method1, method2);\
}\
}


@interface FoundationMacro : NSObject

@end
