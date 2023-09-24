#include "arduino_secrets.h"
#include "thingProperties.h"
#include <Firebase_Arduino_WiFiNINA.h>

// WiFi credentials
#define WIFI_SSID "MONGA PG 3.1"
#define WIFI_PASSWORD "MongaBhai@1"

// LED pins
const int ledPinR = 2;
const int ledPinG = 3;
const int ledPinB = 4;
const int beeperPin = 5;

// Firebase configuration
#define FIREBASE_HOST "traffic-619c9-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "GwyIW6gqVB2l24tvU53xPvTDfiVr2fzFErApAV5D"

FirebaseData firebaseData;

void setup() 
{
  Serial.begin(9600);

  pinMode(ledPinR, OUTPUT);
  pinMode(ledPinG, OUTPUT);
  pinMode(ledPinB, OUTPUT);
  pinMode(beeperPin, OUTPUT);

  // Initialize Firebase
  initializeFirebase();

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() 
{
  ArduinoCloud.update();
  
  // Fetch the status of the Red LED
  if (Firebase.getString(firebaseData, "/LEDs/redLedStatus")) 
  {
    String redStatus = firebaseData.stringData();
    if( redStatus == "RED ON")
    {
      digitalWrite(ledPinR, HIGH);
      tone(beeperPin, 3000);
      red = 1;
    }
    else
    {
      digitalWrite(ledPinR, LOW);
      noTone(beeperPin);
      red = 0;
    }
    
    ArduinoCloud.update();
  } 
  else 
  {
    Serial.print("Error in getString, ");
    Serial.println(firebaseData.errorReason());
  }

  // Fetch the status of the Green LED
  if (Firebase.getString(firebaseData, "/LEDs/greenLedStatus")) 
  {
    String greenStatus = firebaseData.stringData();
    if( greenStatus == "GREEN ON")
    {
      digitalWrite(ledPinG, HIGH);
      tone(beeperPin, 3000);
      green = 1;
    }
    else
    {
      digitalWrite(ledPinG, LOW);
      noTone(beeperPin);
      green = 0;
    }
    
    ArduinoCloud.update();
  } 
  else 
  {
    Serial.print("Error in getString, ");
    Serial.println(firebaseData.errorReason());
  }

  // Fetch the status of the Blue LED
  if (Firebase.getString(firebaseData, "/LEDs/blueLedStatus")) 
  {
    String blueStatus = firebaseData.stringData();
    if( blueStatus == "BLUE ON")
    {
      digitalWrite(ledPinB, HIGH);
      tone(beeperPin, 3000);
      blue = 1;
    }
    else
    {
      digitalWrite(ledPinB, LOW);
      noTone(beeperPin);
      blue = 0;
    }
    
    ArduinoCloud.update();
  } 
  else 
  {
    Serial.print("Error in getString, ");
    Serial.println(firebaseData.errorReason());
  }
}

void initializeFirebase()
{
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH, WIFI_SSID, WIFI_PASSWORD);
  Firebase.reconnectWiFi(true);
}