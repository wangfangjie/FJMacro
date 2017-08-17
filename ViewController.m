//
//  ViewController.m
//  FJMacro
//
//  Created by wangfj on 2017/8/17.
//  Copyright © 2017年 FJMacro. All rights reserved.
//

#import "ViewController.h"
#import "FoundationMacro.h"
#import "UIKitMacro.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    CGFloat h = SCREEN_HEIGHT;
    CGFloat w = SCREEN_WIDTH;
    LOG(@"屏幕宽度==%f和高度==%f",w,h);
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
