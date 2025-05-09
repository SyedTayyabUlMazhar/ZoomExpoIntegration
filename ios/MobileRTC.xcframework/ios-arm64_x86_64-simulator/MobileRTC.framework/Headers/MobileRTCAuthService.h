//
//  MobileRTCAuthService.h
//  MobileRTC
//
//  Created by Zoom Communications on 8/8/14.
//  Copyright (c) Zoom Communications, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MobileRTC/MobileRTCConstants.h>
#import <MobileRTC/MobileRTCNotificationServiceHelper.h>

@protocol MobileRTCAuthDelegate;
@class MobileRTCAccountInfo;
@class MobileRTCAlternativeHost;

/*!
 @brief The method provides support for authorizing MobileRTC.
 @warning Users should authorize MobileRTC before using it to avoid invalid functions in MobileRTC.
 */
@interface MobileRTCAuthService : NSObject

/*!
 @brief The property to receive authentication/login events. 
 */
@property (weak, nonatomic) id<MobileRTCAuthDelegate> _Nullable delegate;

/*!
 @brief jwt auth token.
 @warning Keep the value as a secret. DO NOT publish it. If jwtToken is nil or empty,We will user your appKey and appSecret to Auth, We recommend using JWT Token,  and generate JWT Token on your web backend.
 */
@property (nullable, retain, nonatomic) NSString *jwtToken;

/*!
 @brief Authenticate SDK.
 @warning if you want to auth with jwt token, please fill the token property. Otherwise, please fill the client key and client secret property.
 @warning If the key or secret of client is blank, user will get error:MobileRTCAuthError_KeyOrSecretEmpty via onMobileRTCAuthReturn defined in MobileRTCAuthDelegate.
 */
- (void)sdkAuth;

/*!
 @brief Check whether mobileRTC is logged-in or not.
 @return YES indicates logged-in. Otherwise not.
 @warning The method is optional, ignore it if you do not log in with working email or SSO.
 */
- (BOOL)isLoggedIn;

/*!
 @brief Get user type.
 @return One of the user types listed in MobileRTCUserType.
 @warning The method is optional. The default user type is MobileRTCUserType_APIUser. User who logs in MobileRTC with working email is MobileRTCUserType_ZoomUser; User who logs in MobileRTC with SSO is MobileRTCUserType_SSOUser.
 */
- (MobileRTCUserType)getUserType;

/*!
* @brief generate the sso login url for specific sso vanity url
* @param vanityUrl The prefix of vanity url.
* @return If the function succeeds,will return url of can launch app.
*/
- (nullable NSString *)generateSSOLoginWebURL:(nonnull NSString*)vanityUrl;

/**
 * @brief Login ZOOM with SSO Uri Protocol.
 * @param uriProtocol For the parameter to be used for sso account login.
 * @return If the function succeeds, it will return ZoomSDKError_success. Otherwise failed.
 */
- (MobileRTCLoginFailReason)ssoLoginWithWebUriProtocol:(nonnull NSString*)uriProtocol;

/*!
 @brief Specify to logout MobileRTC.
 @return YES indicates to call the method successfully. Otherwise not.
 @warning The method is optional, ignore it if you do not login MobileRTC.
 */
- (BOOL)logoutRTC;

/*!
 @brief Specify to get the profile information of logged-in user.
 @return The profile information of logged-in user. 
 @warning You can only get the instance successfully of logged-in user.
 */
- (nullable MobileRTCAccountInfo*)getAccountInfo;

/*!
 @brief Enable or disable auto register notification service. This is disabled by default.
 @param enable YES means enabled, otherwise not.
 */
- (void)enableAutoRegisterNotificationServiceForLogin:(BOOL)enable;

/*!
 @brief Register notification service.
 @param accessToken Initialize parameter of notification service.
 @return If the function succeeds, it will return MobileRTCSDKError_Success. Otherwise failed.
 */
- (MobileRTCSDKError)registerNotificationService:(nullable NSString*)accessToken;

/*!
 @brief Unregister notification service.
 @return If the function succeeds, it will return MobileRTCSDKError_Success. Otherwise failed.
 */
- (MobileRTCSDKError)unregisterNotificationService;

/*!
 @brief Get notification service controller interface.
 @return If the function succeeds, it will return a ZoomSDKZpnsServiceController object.
 */
- (MobileRTCNotificationServiceHelper*_Nullable)getNotificationServiceHelper;

@end

/*!
 @brief An authentication service will issue the following values when the authorization state changes.
 */
@protocol MobileRTCAuthDelegate <NSObject>

@required
/*! 
 @brief Specify to get the response of MobileRTC authorization.
 @param returnValue Notify the user that the authorization status changes.
 */
- (void)onMobileRTCAuthReturn:(MobileRTCAuthError)returnValue;

@optional
/*!
 @brief Specify the token expired.
 */
- (void)onMobileRTCAuthExpired;

/*!
 @brief Specify to get the response of MobileRTC logs in.
 @param resultValue Notify the user when the login state has changed.
 @warning If the callback is implemented, the Zoom UI alert tips are no longer displayed.
 */
- (void)onMobileRTCLoginResult:(MobileRTCLoginFailReason)resultValue;

/*!
 @brief Specify to get the response of MobileRTC logs out.
 @param returnValue Notify that the user has logged-out successfully.
 */
- (void)onMobileRTCLogoutReturn:(NSInteger)returnValue;

/*!
 @brief Notification service status changed callback.
 @param status The value of transfer meeting service. For more details, see {@link ZoomSDKNotificationServiceStatus}.
 @param error Connection Notification service fail error code. For more details, see {@link ZoomSDKNotificationServiceError}.
 */
- (void)onNotificationServiceStatus:(MobileRTCNotificationServiceStatus)status error:(MobileRTCNotificationServiceError)error;

@end

/*!
 @brief It is used to store the profile information of logged-in user.
 */
@interface MobileRTCAccountInfo : NSObject

/*!
 @brief Get the working email address.
 @return The working email address.
 */
- (nullable NSString*)getEmailAddress;

/*!
 @brief Get the username of a logged in account. [Login User Only]
 @return Username of the logged in account.
 */
- (nullable NSString*)getUserName;

/*!
 @brief Get PMI Vanity URL from user profile information. 
 @return PMI Vanity URL.
 */
- (nullable NSString *)getPMIVanityURL;

/*!
 @brief Check if Audio Type(Telephone Only) is supported while scheduling a meeting.
 @return YES means support. Otherwise not.
 */
- (BOOL)isTelephoneOnlySupported;

/*!
 @brief Check if Audio Type(Telephone And VoIP) is supported while scheduling a meeting.
 @return YES means support. Otherwise not.
 */
- (BOOL)isTelephoneAndVoipSupported;

/*!
 @brief Check if Audio Type (3rdParty Audio) is supported while scheduling a meeting.
 @return YES means support. Otherwise not.
 */
- (BOOL)is3rdPartyAudioSupported;

/*!
 @brief Get the 3rd Party Audio Info from user profile.
 @return The 3rd Party Audio Info.
 */
- (nullable NSString *)get3rdPartyAudioInfo;

/*!
 @brief Get the default Audio Type from user profile.
 @return The default Audio Type.
 */
- (MobileRTCMeetingItemAudioType)getDefaultAudioInfo;

/*!
 @brief Check if only signed-in user can join the meeting while scheduling a meeting.
 @return YES means that only signed-in user is allowed to join the meeting. Otherwise not.
 */
- (BOOL)onlyAllowSignedInUserJoinMeeting;

/*!
 @brief Get alternative host list from user profile information.
 @return An array with MobileRTCAlternativeHost information.
 */
- (nullable NSArray <MobileRTCAlternativeHost *> *)getCanScheduleForUsersList;

/*!
 @brief Check if local recording is supported while scheduling a meeting.
 @return YES means supported. Otherwise not.
 */
- (BOOL)isLocalRecordingSupported;

/*!
 @brief Check if cloud recording is supported while scheduling a meeting.
 @return YES means supported. Otherwise not.
 */
- (BOOL)isCloudRecordingSupported;

/*!
 @brief Get the default Meeting Auto Recording Types from user profile.
 @return The default Meeting Auto Recording Type.
 */
- (MobileRTCMeetingItemRecordType)getDefaultAutoRecordType;

/*!
 @brief Check if only user in specified domain can join the meeting while scheduling a meeting.
 @return YES means that only user in specified domain can join the meeting. Otherwise not.
 */
- (BOOL)isSpecifiedDomainCanJoinFeatureOn;

/*!
 @brief Get specified domain from user profile.
 @return The data in domain array is NSString type.
 */
- (nullable NSArray <NSString *> *)getDefaultCanJoinUserSpecifiedDomains;

@end

/*!
 @brief It is used to store the information of the alternative host.
 */
@interface MobileRTCAlternativeHost : NSObject

@property (nonatomic, retain, readonly) NSString * _Nullable email;
@property (nonatomic, retain, readonly) NSString * _Nullable firstName;
@property (nonatomic, retain, readonly) NSString * _Nullable lastName;
@property (nonatomic, assign, readonly) unsigned long long PMINumber;

- (id _Nonnull)initWithEmailAddress:(NSString * _Nonnull)emailAddress firstname:(NSString * _Nonnull)firstName lastName:(NSString * _Nonnull)lastName PMI:(unsigned long long)PMINumber;
@end
