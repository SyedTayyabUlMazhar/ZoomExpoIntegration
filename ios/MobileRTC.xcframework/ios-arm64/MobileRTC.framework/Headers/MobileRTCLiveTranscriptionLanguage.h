//
//  MobileRTCLiveTranscriptionLanguage.h
//  MobileRTC
//
//  Created by Zoom on 2022/5/30.
//  Copyright © Zoom Communications, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface MobileRTCLiveTranscriptionLanguage : NSObject

/*!
@brief language id of transcription language
*/
@property(nonatomic, assign, readonly) NSInteger languageID;

/*!
@brief localized language name of transcription language
*/
@property(nonatomic, copy, readonly) NSString * _Nullable languageName;

@end

NS_ASSUME_NONNULL_END
