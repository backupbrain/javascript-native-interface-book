//
//  ReactNativeJsiBridge.m
//  YourProjectName
//
//  Created by Adonis Gaitatzis on 4/7/24.
//

#import "ReactNativeJsiBridge.h"
#import <React/RCTBridge+Private.h>
#import <React/RCTUtils.h>
#import <React/RCTLog.h>
#import "exampleJsiLibrary.h"

@implementation ReactNativeJsiBridge

@synthesize bridge = _bridge;
@synthesize methodQueue = _methodQueue;

RCT_EXPORT_MODULE()

+ (BOOL)requiresMainQueueSetup {
  return YES;
}

- (void)setBridge:(RCTBridge *)bridge {
  _bridge = bridge;
  _setBridgeOnMainQueue = RCTIsMainQueue();
  RCTCxxBridge *cxxBridge = (RCTCxxBridge *)self.bridge;
  RCTLogInfo(@"Setting bridge");
  if (cxxBridge.runtime) {
    RCTLogInfo(@"Running  MyJsiNamespace::installExampleJsiLibrary()");
    MyJsiNamespace::installExampleJsiLibrary(
                                             *(facebook::jsi::Runtime *)cxxBridge.runtime
                                             );
  } else {
    RCTLogInfo(@"cxxBridge not found");
  }
}

@end
