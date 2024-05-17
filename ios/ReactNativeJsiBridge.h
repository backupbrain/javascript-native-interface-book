//
//  ReactNativeJsiBridge.h
//  YourProjectName
//
//  Created by Adonis Gaitatzis on 5/1/24.
//

#import "../cpp/exampleJsiLibrary.h"
#import <React/RCTBridgeModule.h>

@interface ReactNativeJsiBridge : NSObject <RCTBridgeModule>

@property(nonatomic, assign) BOOL setBridgeOnMainQueue;

@end
