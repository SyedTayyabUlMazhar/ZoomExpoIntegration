# Add project specific ProGuard rules here.
# By default, the flags in this file are appended to flags specified
# in /usr/local/Cellar/android-sdk/24.3.3/tools/proguard/proguard-android.txt
# You can edit the include path and order by changing the proguardFiles
# directive in build.gradle.
#
# For more details, see
#   http://developer.android.com/guide/developing/tools/proguard.html

# react-native-reanimated
-keep class com.swmansion.reanimated.** { *; }
-keep class com.facebook.react.turbomodule.** { *; }

# Add any project specific keep options here:
-keep class  us.zoom.**{*;}
-keep class  com.zipow.**{*;}
-keep class  us.zipow.**{*;}
-keep class  org.webrtc.**{*;}
-keep class  us.google.protobuf.**{*;}
-keep class  com.google.crypto.tink.**{*;}
-keep class  androidx.security.crypto.**{*;}
-dontwarn com.android.**
-dontwarn com.google.**
-dontwarn com.microsoft.**
-dontwarn com.zipow.**
-dontwarn javax.lang.**
-dontwarn kotlin.jvm.internal.**
-dontwarn kotlinx.parcelize.**
-dontwarn org.**
-dontwarn us.zoom.**
-dontwarn xcrash.**
-dontwarn java.awt.**
-dontwarn javax.swing.**
