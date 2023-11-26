#include <Blynk.h>

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Definisikan pin untuk sensor hujan dan sensor water level
const int rainSensorPin = D1;  // Pin sensor hujan terhubung ke pin D1 pada ESP8266
const int waterLevelSensorPin = D2;  // Pin sensor water level terhubung ke pin D2 pada ESP8266

// Kredensial Blynk
char auth[] = "cc7kp1gIhXLAtDM3VIlvZJrEgum--NO5";  // Ganti dengan token otentikasi Blynk Anda
const char *ssid = "meow";  // Ganti dengan nama WiFi Anda
const char *password = "kayabiasa";  // Ganti dengan kata sandi WiFi Anda

void setup() {
  // Mulai serial communication
  Serial.begin(115200);

  // Inisialisasi sensor hujan dan sensor water level
  pinMode(rainSensorPin, INPUT);
  pinMode(waterLevelSensorPin, INPUT);

  // Hubungkan ke jaringan WiFi
  connectToWiFi();

  // Mulai koneksi ke Blynk
  Blynk.begin(auth, ssid, password);
}

void loop() {
  // Perbarui koneksi Blynk
  Blynk.run();

  // Baca nilai sensor hujan dan sensor water level
  int rainValue = digitalRead(rainSensorPin);
  int waterLevelValue = digitalRead(waterLevelSensorPin);

  // Kirim nilai sensor ke Blynk
  Blynk.virtualWrite(V1, rainValue);
  Blynk.virtualWrite(V2, waterLevelValue);

  // Tunda selama 10 detik sebelum membaca ulang sensor
  delay(10000);
}

// Fungsi untuk menghubungkan ke jaringan WiFi
void connectToWiFi() {
  Serial.println("Menghubungkan ke WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Mencoba menghubungkan...");
  }

  Serial.println("Terhubung ke WiFi");
}
