#include "RTClib.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_ADS1X15.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_SHT31.h" 


Adafruit_SHT31 sht31 = Adafruit_SHT31();

// firebase lib and var
#include <WiFi.h>
#include <PubSubClient.h>

WiFiClient espClient;
PubSubClient mqttClient(espClient);


unsigned long sendDataPrevMillis = 0;
const char* ssid = "Matahari";
const char* password = "Wima2023";
const char* mqttServer = "192.168.100.9";
const int mqttPort = 1883;
char* mqttUser;
const char* mqttUsername = "bara";
const char* mqttPassword = "Sandibaru2002!";
const char* pubTopic = "kontrol";
const char* subTopic;

/*
  const char* mqttServer = "e1a8b3491b2b46d49b7b1962482f02ab.s1.eu.hivemq.cloud";
  const int mqttPort = 8884;
  char* mqttUser = "admin";
  const char* mqttPassword = "Admin123";
  const char* pubTopic;
  const char* subTopic;

  WiFiClient espClient;
  PubSubClient mqttClient(espClient);*/

// Kalibrasi double point DO sensor
//Single point calibration needs to be filled CAL1_V and CAL1_T
#define CAL1_V (1205) //mv
#define CAL1_T (30.25)   //℃
//Two-point calibration needs to be filled CAL2_V and CAL2_T
//CAL1 High temperature point, CAL2 Low temperature point
#define CAL2_V (1300) //mv
#define CAL2_T (15)   //℃
// jadi dilakukan pembacaan voltase pada air yang sama dengan suhu berbeda
#define TWO_POINT_CALIBRATION 0

RTC_DS3231 rtc;
Adafruit_ADS1115 ads;

// GPIO where the DS18B20 is connected to
const int oneWireBus = 4;

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature thermo(&oneWire);

float temperature;       // current temperature for compensation

String node_id = "1";
bool connectWifi = false, data1 = false;
String Timestamp;
String packetData;

uint32_t startKirim = 0;

String suhu_w, hum_, suhu_a, tds_, ph_, do_, status_, batt_, time_;
int led1 = 0,
    led2 = 2;

TaskHandle_t Task1;
TaskHandle_t Task2;

void initiate();
void connectToWiFi();

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600);
  
  initiate();
  xTaskCreatePinnedToCore(Task1code, "Task1", 10000, NULL, 1, &Task1, 0); 

  xTaskCreatePinnedToCore(Task2code, "Task2", 10000, NULL, 1, &Task2, 1); 

}
void Task1code( void * parameter ) {

  for (;;) {
    reading();
    nextion_data();
    
    delay(1000);
  }
}

void Task2code( void * parameter ) { // Untuk receive dan parsing data

  for (;;) {
    if (connectWifi == false){
      connectToWiFi();
      mqtt_begin();
      digitalWrite(led2, HIGH);
      connectWifi = true;
    }
    mqttClient.loop();
    if (millis() - sendDataPrevMillis > 1000) {
      
      packetData = suhu_w + "," + do_ + "," + ph_ + "," + tds_ + "," + Timestamp;
      const char * bufferGateway = packetData.c_str();
      publishMessage(bufferGateway);
      sendDataPrevMillis = millis();
    }
    if (WiFi.status() != WL_CONNECTED) {  // Cek koneksi WiFi
      Serial.println("Koneksi WiFi terputus, mencoba kembali...");
      String display_data = "wifi.txt=\"" + String("recon") + "\"";
      Serial2.print(display_data);
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      digitalWrite(led2, LOW);
      connectToWiFi();  // Jika koneksi terputus, panggil fungsi untuk menghubungkan kembali
    }
    delay(10);
  }
}
void Task3code( void * parameter ) {
  }
void loop() {

}

void initiate() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  digitalWrite(led1, HIGH);
  DS3231_begin();
  thermo.begin();
  ads.begin();
  for(int o = 0; o <= 3; o++){
    ads.readADC_SingleEnded(o); 
  }
  
  if (! sht31.begin(0x44)) {   // Set to 0x45 for alternate i2c addr
      Serial.println("Couldn't find SHT31");
      while (1) delay(1);
      }
  
}

void reading() {
  suhu_w = thermo_read();
  suhu_a = dht_read_t();
  hum_ = dht_read_h();
  tds_ = tds_read();
  ph_ = pH_read();
  do_ = do_read(temperature);
  batt_ = battery_read();
  time_ = DS3231_read();
  Serial.println("Suhu air : " + suhu_w);
  Serial.println("Suhu udara : " + suhu_a);
  Serial.println("Kelembaban : " + hum_);
  Serial.println("TDS : " + tds_);
  Serial.println("pH : " + ph_);
  Serial.println("DO : " + do_);
  Serial.println("Battery : " + batt_);
  Serial.println("Time : " + time_);
  
}
