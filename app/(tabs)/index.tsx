import {
  Image,
  StyleSheet,
  Platform,
  TextInput,
  TouchableOpacity,
  Alert,
  Text,
} from "react-native";

import { HelloWave } from "@/components/HelloWave";
import ParallaxScrollView from "@/components/ParallaxScrollView";
import { ThemedText } from "@/components/ThemedText";
import { ThemedView } from "@/components/ThemedView";
import { useState } from "react";
import { useZoom, ZoomSDKProvider } from "@zoom/meetingsdk-react-native";

export default function HomeScreen() {
  const [meetingNumber, setMeetingNumber] = useState("79475845346");
  const [meetingPassword, setMeetingPassword] = useState("FgP34n");
  const [displayName, setDisplayName] = useState("John");
  const [zak, setZak] = useState("");

  const [jwtToken, setJwt] = useState("eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhcHBLZXkiOiJ2OG5xUEdJX1NSR3BNOWx5SVN6Z2xBIiwic2RrS2V5IjoidjhucVBHSV9TUkdwTTlseUlTemdsQSIsIm1uIjoiNzk0IDc1ODQgNTM0NiIsInJvbGUiOjAsInRva2VuRXhwIjoxNzM5NTQ5NDkyLCJpYXQiOjE3Mzk1NDU4OTIsImV4cCI6MTczOTU0OTQ5Mn0.Y5vwOzK3U2xlZIp5X05yh-QtjrCI5QHF-gptNhNKo9k");

  return (
    <ParallaxScrollView
      headerBackgroundColor={{ light: "#A1CEDC", dark: "#1D3D47" }}
      headerImage={
        <Image
          source={require("@/assets/images/partial-react-logo.png")}
          style={styles.reactLogo}
        />
      }
    >
      <ThemedView style={styles.titleContainer}>
        <ThemedText type="title">Welcome!</ThemedText>
        <HelloWave />
      </ThemedView>
      <ThemedView>
        <TextInput
          placeholder="JWT Token"
          value={jwtToken}
          onChangeText={(value) => setJwt(value)}
          style={styles.input}
        />
        <TextInput
          placeholder="Meeting Id"
          value={meetingNumber}
          onChangeText={(value) => setMeetingNumber(value)}
          style={styles.input}
        />
        <TextInput
          placeholder="Meeting Password"
          value={meetingPassword}
          onChangeText={(value) => setMeetingPassword(value)}
          style={styles.input}
        />
        <TextInput
          placeholder="Name"
          value={displayName}
          onChangeText={(value) => setDisplayName(value)}
          style={styles.input}
        />
      </ThemedView>
      <ThemedView style={styles.stepContainer}>
        {jwtToken?.trim() ? (
          <ZoomSDKProvider
            config={{
              jwtToken: jwtToken,
              domain: "zoom.us",
              enableLog: true,
              logSize: 5,
            }}
          >
            <Buttons
              displayName={displayName}
              meetingNumber={meetingNumber}
              meetingPassword={meetingPassword}
              zak={zak}
            />
          </ZoomSDKProvider>
        ) : null}
        <ThemedText type="subtitle">Step 1: Try it</ThemedText>
        <ThemedText>
          Edit{" "}
          <ThemedText type="defaultSemiBold">app/(tabs)/index.tsx</ThemedText>{" "}
          to see changes. Press{" "}
          <ThemedText type="defaultSemiBold">
            {Platform.select({
              ios: "cmd + d",
              android: "cmd + m",
              web: "F12",
            })}
          </ThemedText>{" "}
          to open developer tools.
        </ThemedText>
      </ThemedView>
      <ThemedView style={styles.stepContainer}>
        <ThemedText type="subtitle">Step 2: Explore</ThemedText>
        <ThemedText>
          Tap the Explore tab to learn more about what's included in this
          starter app.
        </ThemedText>
      </ThemedView>
      <ThemedView style={styles.stepContainer}>
        <ThemedText type="subtitle">Step 3: Get a fresh start</ThemedText>
        <ThemedText>
          When you're ready, run{" "}
          <ThemedText type="defaultSemiBold">npm run reset-project</ThemedText>{" "}
          to get a fresh <ThemedText type="defaultSemiBold">app</ThemedText>{" "}
          directory. This will move the current{" "}
          <ThemedText type="defaultSemiBold">app</ThemedText> to{" "}
          <ThemedText type="defaultSemiBold">app-example</ThemedText>.
        </ThemedText>
      </ThemedView>
    </ParallaxScrollView>
  );
}

type ButtonsProps = {
  meetingNumber?: string;
  displayName?: string;
  meetingPassword?: string;
  zak?: string;
};
const Buttons = (props: ButtonsProps) => {
  const {
    meetingNumber = "",
    displayName = "",
    meetingPassword = "",
    zak = "",
  } = props;
  const zoom = useZoom();

  const joinMeeting = async () => {
    if (!meetingNumber.trim()) {
      Alert.alert("Please Enter Valid Meeting Number");
      return;
    }
    if (!displayName.trim()) {
      Alert.alert("Please Enter Display Name");
      return;
    }
    if (!meetingPassword.trim()) {
      Alert.alert("Please Enter Password");
      return;
    }
    try {
      console.log("DEBUG: joining");
      const result = await zoom.joinMeeting({
        userName: displayName,
        meetingNumber: meetingNumber,
        password: meetingPassword,
        userType: 1,
      });
      console.log("DEBUG: joined result:", result);
    } catch (e) {
      console.log(e);
      Alert.alert("Failed to join the meeting" + e);
    }
  };

  const startMeeting = async () => {
    if (!displayName.trim()) {
      Alert.alert("Please Enter Display Name");
      return;
    }
    if (!zak.trim()) {
      Alert.alert("Please Enter ZAK Token");
      return;
    }
    try {
      await zoom.startMeeting({
        userName: displayName,
        meetingNumber: meetingNumber,
        zoomAccessToken: zak,
      });
    } catch (e) {
      console.log(e);
      Alert.alert("Failed to start the meeting" + e);
    }
  };
  return (
    <>
      <TouchableOpacity onPress={startMeeting} style={styles.button}>
        <Text style={styles.buttonText}>{"Create a Meeting"}</Text>
      </TouchableOpacity>
      <TouchableOpacity onPress={joinMeeting} style={styles.button}>
        <Text style={styles.buttonText}>{"Join a Meeting"}</Text>
      </TouchableOpacity>
    </>
  );
};

const styles = StyleSheet.create({
  titleContainer: {
    flexDirection: "row",
    alignItems: "center",
    gap: 8,
  },
  stepContainer: {
    gap: 8,
    marginBottom: 8,
  },
  reactLogo: {
    height: 178,
    width: 290,
    bottom: 0,
    left: 0,
    position: "absolute",
  },
  button: {
    backgroundColor: "#0e71eb",
    alignItems: "center",
    marginTop: 15,
    marginHorizontal: 15,
    paddingVertical: 10,
    borderRadius: 5,
  },
  buttonText: {
    color: "white",
  },
  input: {
    borderWidth: 1,
    borderColor: "gray",
    borderRadius: 5,
    padding: 10,
    marginVertical: 10,
    height: 40,
  }
});
