//
//  main.m
//  Calc
//
//  Created by Merlot on 2024/5/24.
//

#import <Foundation/Foundation.h>
#import "Calc.h"

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        // insert code here...
        NSLog(@"Hello, World!");
        BOOL isOff = NO;
        
        Calc* cl = [[Calc alloc] init];
        double res = [cl sum:1.0 other:1.2];
        NSLog(@"sum %f", res);
        UniChar a = 12;
        NSString* str = @"Hello World";
        NSArray* ar = @[@"1", @"2"];
    }
    return 0;
}
