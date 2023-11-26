#define BLYNK_TEMPLATE_ID "TMPL6nGlJDoEK"
#define BLYNK_TEMPLATE_NAME "Rain Drop Alert"
#define BLYNK_AUTH_TOKEN "kwWWriYiRiv0th0zi5Ur-7Xvt9jf_AbD"

#define BLYNK_PRINT Serial
// #include <Blynk.h>

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

const char* ssid = "meow";
const char* password = "kayabiasa";

const int rainPin = D0;  // Pin untuk sensor hujan
const int waterLevelPin = A0;  // Pin untuk sensor ketinggian air
int buzzerPin = D1; // Pin untuk buzzer
const int thresholdWaterLevel = 1000;  // Ubah nilai ini sesuai dengan tinggi air yang diinginkan
int delayInterval = 5000;  // Jeda pemberitahuan dalam milidetik (10 detik)
bool isRaining = false;

void setup() {
  Serial.begin(115200);

  // Hubungkan ke WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  pinMode(rainPin, INPUT);
  pinMode(waterLevelPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  // Connect blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);
}

void loop() {
  int rainValue = digitalRead(rainPin);

  if (rainValue == LOW) {
    isRaining = true;
    Serial.println("Hujan terdeteksi. Sistem diaktifkan.");
    Blynk.logEvent("rainalert");
    waterlevel();
  } else {
    isRaining = false;
    Serial.println("Tidak ada hujan. Sistem menunggu...");    
    delay(10000);
  }
  delay(1000);
}

void waterlevel(){
  int waterLevelValue = analogRead(waterLevelPin);

  Serial.print("Tinggi Air: ");
  Serial.println(waterLevelValue);

  if (waterLevelValue > thresholdWaterLevel) {
    Serial.println("Banjir terdeteksi!");
    activateBuzzer();
    Blynk.logEvent("alert");
  } else {
    Serial.println("Tidak Ada Banjir");
  }

  Blynk.virtualWrite(V0, waterLevelValue);
  Blynk.run();
}

void activateBuzzer() {
  digitalWrite(buzzerPin, HIGH);
  delay(100);
  digitalWrite(buzzerPin, LOW); 
  delay(100);
}