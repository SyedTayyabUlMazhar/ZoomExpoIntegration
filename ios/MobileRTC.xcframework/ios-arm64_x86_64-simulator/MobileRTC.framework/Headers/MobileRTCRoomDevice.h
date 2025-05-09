//
//  MobileRTCRoomDevice.h
//  MobileRTC
//
//  Created by Zoom Communications on 2017/2/27.
//  Copyright © Zoom Communications, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
 @brief MobileRTCDeviceType Enumeration of room device types.
 */
typedef enum {
    ///H.323 Device
    MobileRTCDeviceType_H323  = 1,
    ///SIP Device
    MobileRTCDeviceType_SIP,
    ///Both
    MobileRTCDeviceType_Both,
}MobileRTCDeviceType;

/*!
 @brief MobileRTCDeviceEncryptType Enumeration of H.323/SIP encryption types.
 */
typedef enum {
    ///Meeting room system is not encrypted.
    MobileRTCDeviceEncryptType_None   = 0,
    ///Meeting room system is encrypted.
    MobileRTCDeviceEncryptType_Encrypt,
    ///Meeting room system is encrypted automatically.
    MobileRTCDeviceEncryptType_Auto,
}MobileRTCDeviceEncryptType;

@interface MobileRTCRoomDevice : NSObject

@property (nonatomic, copy) NSString * _Nullable deviceName;
@property (nonatomic, copy) NSString * _Nullable ipAddress;
@property (nonatomic, copy) NSString * _Nullable e164num;
@property (nonatomic, assign) MobileRTCDeviceType deviceType;
@property (nonatomic, assign) MobileRTCDeviceEncryptType encryptType;

@end
