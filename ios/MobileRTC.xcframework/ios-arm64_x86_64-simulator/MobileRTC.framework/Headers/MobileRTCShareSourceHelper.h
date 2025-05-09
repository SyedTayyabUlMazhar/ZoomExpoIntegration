//
//  MobileRTCShareSourceHelper.h
//  MobileRTC
//
//  Created by Zoom on 2022/6/30.
//  Copyright © Zoom Communications, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface MobileRTCShareSourceHelper : NSObject

/*!
@brief Start sharing external source.
@param shareDelegate The external source object pointer. Please See MobileRTCShareSourceDelegate
@param audioDelegate .The external audio source object pointer.  Please See MobileRTCShareAudioSourceDelegate.
@return return If the function succeeds, the return value is MobileRTCRawData_Success.
@warning If audioDelegate is non-null, it indicates sharinge user-defined audio at the same time
*/
- (MobileRTCRawDataError)setExternalShareSource:(id<MobileRTCShareSourceDelegate> _Nullable)shareDelegate andAudioSource:(id <MobileRTCShareAudioSourceDelegate> _Nullable)audioDelegate;

@end

