//
//  UIKitMacro.h
//  FJMacro
//
//  Created by wangfj on 2017/8/17.
//  Copyright © 2017年 FJMacro. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <UIKit/UIDevice.h>
#import "FoundationMacro.h"


//----------------------screen size-------------------------
//----------------------屏幕尺寸-------------------------

#define SCREEN_BOUND        ([UIScreen mainScreen].bounds)

#define SCREEN_WIDTH         ([UIScreen mainScreen].bounds.size.width)

#define SCREEN_HEIGHT        ([UIScreen mainScreen].bounds.size.height)

#define SCREEN_SCALE         ([UIScreen mainScreen].scale)

#define STATUSBAR_HEIGHT     ([[UIApplication sharedApplication] statusBarFrame].size.height)

#define NAVIBAR_HEIGHT (self.navigationController.navigationBar.frame.size.height)



//----------------Screen adaptation--------------------
//--------------------屏幕适配---------------------------

// Usually UI to design mark could not have a variety of screen when mark respectively, too much trouble, need only gives an annotation of the screen, then we selected by default if iPhone6 screen design, according to the proportion iPhone6 screen automatically adapt to the other screen

// iphone4 iphone 5 iPhone7 are in accordance with the (w = 375) coded as a benchmark rate adaptive

// 通常UI给设计图标注的时候不可能多种屏幕分别标注，太麻烦了，需要只给一种屏幕的标注就行，那么我们默认选中只要iPhone6屏幕的设计图标注，其他屏幕根据iPhone6屏幕比例自动适应

// iphone4 iphone5 iPhone7 都按照(w=375)标注为基准比例自适应
#define ADJUST_WIDTH(width)              (floorf((width) * SCREEN_WIDTH/ 375.0f))

// iphone4 iphone 5 iPhone7 are in accordance with the (h=667) coded as a benchmark rate adaptive

// iphone4 iphone5 iPhone7 都按照(h=667)标注为基准比例自适应
#define ADJUST_HEIGHT(height)            (floorf((height) * SCREEN_HEIGHT/ 667.0f))


//---------------Judging device screen---------------------
//--------------------判断设备屏幕---------------------------

//iphone4的屏幕
#define IS_IPHONE4_4S ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(320, 480), [UIScreen mainScreen].bounds.size) : NO)

//iphone5的屏幕
#define IS_IPHONE5_5S ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(320, 568), [UIScreen mainScreen].bounds.size) : NO)

//iphone6和iPhone7的屏幕
#define IS_IPHONE6_6S_7 ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(375, 667), [UIScreen mainScreen].bounds.size): NO)

//iphone6P和iPhone7P的屏幕
#define IS_IPHONE6P_67P ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(414, 736), [UIScreen mainScreen].bounds.size) : NO)

//iPad Air,iPad Air2,iPad Pro9.7inch,iPad Retina的屏幕
#define IS_IPAD_AIR_AIR2_PRO9_RETINA ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(768, 1024), [UIScreen mainScreen].bounds.size) : NO)

//iPad Pro12.9inch的屏幕
#define IS_IPAD_PRO12 ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(1024, 1366), [UIScreen mainScreen].bounds.size) : NO)

//--------------------Font---------------------------
//--------------------字体---------------------------

#define FONT(size)        [UIFont systemFontOfSize:(size)]
#define FONT_B(size)      [UIFont boldSystemFontOfSize:(size)]
#define FONT_NAME_SIZE(name,size) [UIFont fontWithName:(name) size:(size)]


//-------------------Color---------------------------
//--------------------颜色---------------------------

#define COLOR_RGB(r,g,b) [UIColor colorWithRed:(r)/255.0 green:(g)/255.0 blue:(b)/255.0 alpha:1.0]

#define COLOR_RGBA(r,g,b,a) [UIColor colorWithRed:(r)/255.0 green:(g)/255.0 blue:(b)/255.0 alpha:a/1.0]

//Hexadecimal color to color object
//16进制数转为颜色对象
//COLOR_RGB(0X1E1E1E);
#define COLOR_HEX_RGB(hexValue) [UIColor colorWith\
Red     :(hexValue & 0xFF0000)     / (float)0xFF0000 \
green   :(hexValue & 0xFF00)       / (float)0xFF00 \
blue    :(hexValue & 0xFF)         / (float)0xFF \
alpha   :1.0]

//16进制数转为颜色对象
//COLOR_RGBA(0X1E1E1E);
#define COLOR_HEX_RGBA(hexValue) [UIColor colorWith\
Red     :(hexValue & 0xFF000000)  / (float)0xFF000000 \
green   :(hexValue & 0xFF0000)    / (float)0xFF0000 \
blue    :(hexValue & 0xFF00)      / (float)0xFF00 \
alpha   :(hexValue & 0xFF)        / (float)0xFF]

//Hexadecimal string color to the color object
//16进制字符串颜色转为颜色对象
//COLOR_HEX(@"#1E1E1E");
#define COLOR_HEX_STR(hexstring)       [UIKitMacro colorWithHexString:(hexstring)]


//--------------------image---------------------------
//--------------------图片---------------------------

#define IMAGE(name)           [UIImage imageNamed:(name)]
#define IMAGE_VIEW(name)      [[UIImageView alloc] initWithImage:IMAGE(name)]

#define IMAGE_FILE(file)        [UIImage imageWithContentsOfFile:file]
#define IMAGE_CG(x)        [UIImage imageWithCGImage:(x)]
#define IMAGE_DATA(data)      [UIImage imageWithData:(data)]

//view to image
//根据视图截屏
#define IMAGE_CAPTURE(view)     [UIKitMacro captureWithView:view];

//获取指定大小的图片，等比例
#define IMAGE_COMPRESS(image,size)     [UIKitMacro compressImage:image toSize:size];

//获取图片根据给定颜色
#define IMAGE_BY_COLOR(color)     [UIKitMacro createImageWithColor:color];


//--------------------AlertView---------------------------
//--------------------警告框---------------------------

#define SHOW_ALERT(message)   _ShowAlertView(0, nil, (message), nil, @"确定", nil)

#define SHOW_ALERTVIEW(_tag_, title, msg, _delegate_, cancelTitle, ...) {\
UIAlertView *alert = [[UIAlertView alloc] initWithTitle: title\
message: msg\
delegate: _delegate_\
cancelButtonTitle: cancelTitle\
otherButtonTitles: __VA_ARGS__];\
alert.tag = _tag_;\
[alert show];\
}



//--------------------ios Version---------------------
//--------------------ios版本---------------------------

#define IOS_VERSION  [UIKitMacro getSystemVersion]

//该方法不准确，只对于整数版本准确，如果输入9.2判断不对因为实际版本9.2.1转为float值为9.199998，小于9.2，所以不能输入小数
#define IOS_VERSION_OR_lALTER(v)  {[UIKitMacro getSystemVersion]>=v?YES:NO}

//以下判断准确可用
#define IOS5_OR_LATER IOS_VERSION_OR_lALTER(5)
#define IOS6_OR_LATER IOS_VERSION_OR_lALTER(6)
#define IOS7_OR_LATER IOS_VERSION_OR_lALTER(7)
#define IOS8_OR_LATER IOS_VERSION_OR_lALTER(8)
#define IOS9_OR_LATER IOS_VERSION_OR_lALTER(9)
#define IOS10_OR_LATER IOS_VERSION_OR_lALTER(10)


//--------------------打印---------------------------

//遍历子视图打印指针地址
#define PRINT_AllVIEW(view)        [UIKitMacro printAllViews:view]

//-----------------------------------------------


@interface UIKitMacro : NSObject

@end
