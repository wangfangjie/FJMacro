//
//  UIKitMacro.m
//  FJMacro
//
//  Created by wangfj on 2017/8/17.
//  Copyright © 2017年 FJMacro. All rights reserved.
//

#import "UIKitMacro.h"

void doPrintViewAndSubviews(UIView *view, int level)
{
    printf("%d--", level);
    for (int i=0; i<level; ++i)
    {
        printf("--");
    }
    NSString *str = [NSString stringWithFormat:@"%@,", view];
    printf("%s\n", [str UTF8String]);
    ++level;
    for (UIView *v in view.subviews)
    {
        doPrintViewAndSubviews(v, level);
    }
}

@implementation UIKitMacro
+(float)getSystemVersion
{
    NSArray *ar = [[UIDevice currentDevice].systemVersion componentsSeparatedByString:@"."];
    
    NSMutableString *str = [[NSMutableString alloc] init];
    if (ar.count>=2) {
        [str appendString:[ar objectAtIndex:0]];
        [str appendString:@"."];
        [str appendString:[ar objectAtIndex:1]];
    }
    else
    {
        [str appendString:[UIDevice currentDevice].systemVersion];
    }
    
    float version = [str floatValue];
    
    return version;
}

+ (UIColor *)colorWithHexString:(NSString *)color
{
    NSString *cString = [[color stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]] uppercaseString];
    
    // String should be 6 or 8 characters
    if ([cString length] < 6) {
        return [UIColor clearColor];
    }
    // 判断前缀
    if ([cString hasPrefix:@"0X"])
        cString = [cString substringFromIndex:2];
    if ([cString hasPrefix:@"#"])
        cString = [cString substringFromIndex:1];
    if ([cString length] != 6)
        return [UIColor clearColor];
    // 从六位数值中找到RGB对应的位数并转换
    NSRange range;
    range.location = 0;
    range.length = 2;
    //R、G、B
    NSString *rString = [cString substringWithRange:range];
    range.location = 2;
    NSString *gString = [cString substringWithRange:range];
    range.location = 4;
    NSString *bString = [cString substringWithRange:range];
    // Scan values
    unsigned int r, g, b;
    [[NSScanner scannerWithString:rString] scanHexInt:&r];
    [[NSScanner scannerWithString:gString] scanHexInt:&g];
    [[NSScanner scannerWithString:bString] scanHexInt:&b];
    
    return [UIColor colorWithRed:((float) r / 255.0f) green:((float) g / 255.0f) blue:((float) b / 255.0f) alpha:1.0f];
}

+(void)printAllViews:(UIView *)view
{
#if DEBUG
    doPrintViewAndSubviews(view, 0);
#endif
}

+ (UIImage*)createImageWithColor:(UIColor *)color;
{
    CGRect rect = CGRectMake(0.0f, 0.0f, 1.0f, 1.0f);
    UIGraphicsBeginImageContext(rect.size);
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGContextSetFillColorWithColor(context, [color CGColor]);
    CGContextFillRect(context, rect);
    UIImage *theImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return theImage;
}

+ (UIImage *)captureWithView:(UIView *)view;
{
    UIImage *ret = nil;
    if (IS_KIND_OF(view, UIScrollView))
    {
        UIScrollView *scrollView = (UIScrollView *)view;
        UIGraphicsBeginImageContextWithOptions(scrollView.contentSize, scrollView.opaque, 0.0);
        {
            CGPoint savedContentOffset = scrollView.contentOffset;
            CGRect savedFrame          = scrollView.frame;
            
            scrollView.frame           = CGRectMake(0, 0, scrollView.contentSize.width, scrollView.contentSize.height);
            scrollView.contentOffset   = CGPointZero;
            
            [scrollView.layer renderInContext: UIGraphicsGetCurrentContext()];
            ret = UIGraphicsGetImageFromCurrentImageContext();
            
            scrollView.frame           = savedFrame;
            scrollView.contentOffset   = savedContentOffset;
        }
        UIGraphicsEndImageContext();
    }
    else
    {
        UIGraphicsBeginImageContextWithOptions(view.bounds.size, NO, 0.0);
        [view.layer renderInContext:UIGraphicsGetCurrentContext()];
        ret = UIGraphicsGetImageFromCurrentImageContext();
        UIGraphicsEndImageContext();
    }
    return (ret);
}

+ (UIImage *)compressImage:(UIImage *)image toSize:(CGSize)size
{
    size.width = MAX(10, size.width);
    size.height = MAX(10, size.height);
    
    CGSize sz = image.size;
    float ss = (sz.height >= 10) ? (sz.width / sz.height) : 1;
    int w = MIN(size.height * ss, MIN(sz.width, size.width));
    int h = MIN(size.width / ss, MIN(sz.height, size.height));
    
    UIGraphicsBeginImageContext(CGSizeMake(w, h));
    [image drawInRect:CGRectMake(0, 0, w, h)];
    UIImage *compressImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return (compressImage);
}

@end
