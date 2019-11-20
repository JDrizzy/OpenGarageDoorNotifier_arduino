#include <ESP8266WiFi.h>
#include <SmsGlobal.h>

const char *ssid = "<wifi_ssid>";
const char *password = "<wifi_password>";

const char *sms_global_user = "<user>";
const char *sms_global_password = "<password>";
const char *sms_to = "<mobile_number>";

const int REED_PIN = D6;

SmsGlobal smsGlobal(sms_global_user, sms_global_password);

void setup() {
  pinMode(REED_PIN, INPUT_PULLUP);

  Serial.begin(115200);

  delay(100);
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (digitalRead(REED_PIN) == LOW) {
    Serial.println("Garage door is open");
    delay(600000); // 10 minutes
    if (digitalRead(REED_PIN) == LOW) {
      Serial.println("Garage door is still open - sending message");
      smsGlobal.send("Garage Door", sms_to, "You left me open!");
    }
  } else {
    Serial.println("Garage door closed");
  }

  Serial.println("ESP8266 in sleep mode");
  ESP.deepSleep(3e8); // 5 minutes
}

void loop() { }
