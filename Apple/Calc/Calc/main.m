//
//  main.m
//  Calc
//
//  Created by Merlot on 2024/5/24.
//

#import <Foundation/Foundation.h>
#import "Calc.h"

/*
 @brief 基本数据类型
 Objective-C的数据类型和C保持一致，同时做了扩展，但是基本数据类型还是一样的
 
 同时扩展了BOOL类型，作为YES,NO的模型
 
 
 
 */

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        // insert code here...
        NSLog(@"Hello, World!");
        BOOL isOff = NO;
        
        Calc* cl = [[Calc alloc] init];
        double res = [cl sum:1.0 other:1.2];
        NSLog(@"sum %f", res);
    }
    return 0;
}
