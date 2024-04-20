//Fuzzy lib
#include <Fuzzy.h>

// MQTT lib and var
#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Matahari";
const char* password = "Wima2023";
const char* mqttServer = "192.168.100.9";
const int mqttPort = 1883;
char* mqttUser;
const char* mqttUsername = "bara";
const char* mqttPassword = "Sandibaru2002!";
const char* pubTopic;
const char* subTopic;

WiFiClient espClient;
PubSubClient mqttClient(espClient);
bool connectWifi = false;

//variabel data
String dataRaw;
bool listen = false, paketData = false;
int TDS, jam, menit, detik, unixDetik = 0;
float suhu, DO, pH, errorDO, merrorDO, derrorDO;
int setPoint;

//IO
/*
13 paling kanan
12
14
27
26
25 paling kiri
*/

int r1 = 34,
    r2 = 35,
    r3 = 32,
    r4 = 33,
    m1 = 25,
    m2 = 26,
    m3 = 27,
    m4 = 14,
    m5 = 12,
    m6 = 13;

// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;
const int ledPin = 26;  // pin io

void setup() {
  Serial.begin(115200);
  fuzzy_begin();
  
  // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(ledPin, ledChannel);

  ledcWrite(ledChannel, 255);
  delay(1000);
  ledcWrite(ledChannel, 50);
  setPoint = 60;
}

void loop() {
  //Komunikasi
  if (WiFi.status() != WL_CONNECTED) {  // Reconnect
    Serial.println("Koneksi WiFi terputus, mencoba kembali...");
    wifiBegin();  // Jika koneksi terputus, panggil fungsi untuk menghubungkan kembali
    MQTTBegin();

    //jika reconnect data yang harus di proses bagaimana(?)
    paketData = false;
  }

  MQTTBegin();
  

  //Data process
  if(paketData == false){
    ledcWrite(ledChannel, 0);
  }
  merrorDO = errorDO;    //memorry delta error DO
  if (listen == true) {  //data dikirim 1Hz, coba mainin frekuensi pengirimannya coba
    parseData(dataRaw);
    //defuzzy(); //Defuzzyfication
    ledcWrite(ledChannel, defuzzy());
    paketData = true;
  }
  mqttClient.loop();
  //delay(1000);
}

void wifiBegin() {
  WiFi.setTxPower(WIFI_POWER_19_5dBm);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void MQTTBegin() {
  mqttClient.setServer(mqttServer, mqttPort);
  while (!mqttClient.connected()) {
    String mqtt_clientId = "mesh_gateway-";
    mqtt_clientId += String(random(0xffff), HEX);

    if (mqttClient.connect("ESP8266Client", "bara", mqttPassword)) {
      Serial.println("Connected to MQTT broker");

    } else {
      Serial.print("Failed to connect to MQTT broker, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" Retrying in 5 seconds...");

      delay(5000);
    }
    mqttClient.subscribe("kontrol",1);
  }
  mqttClient.setCallback(callback);
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageRcv;

  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageRcv += (char)message[i];
  }
  Serial.println();
  dataRaw = messageRcv;
  listen = true;
}

void parseData(String data) {
  // Gunakan strtok untuk membagi string berdasarkan koma
  char* token = strtok((char*)data.c_str(), ",");

  // Mengambil nilai-nilai yang sesuai dan mengonversinya ke tipe data yang sesuai
  if (token != NULL) {
    suhu = atof(token);
    token = strtok(NULL, ",");
  }
  if (token != NULL) {
    DO = atof(token);
    token = strtok(NULL, ",");
  }
  if (token != NULL) {
    pH = atof(token);
    token = strtok(NULL, ",");
  }
  if (token != NULL) {
    TDS = atoi(token);
    token = strtok(NULL, ",");
  }
  if (token != NULL) {
    jam = atoi(token);
    token = strtok(NULL, ",");
  }
  if (token != NULL) {
    menit = atoi(token);
    token = strtok(NULL, ",");
  }
  if (token != NULL) {
    detik = atoi(token);
  }
  DO = DO * 10; // normalisasi 10
  errorDO = setPoint - DO;
  if (paketData == 0) {
    derrorDO = 0;
  }else{
    derrorDO = merrorDO - errorDO;
  }
  unixDetik = (jam * 60 * 60) + (menit * 60) + (detik);

  // Cetak nilai-nilai yang sudah diparsing
  Serial.print("Value 1: ");
  Serial.println(suhu, 2);  // Menampilkan 2 desimal
  Serial.print("Value 2: ");
  Serial.println(DO, 2);
  Serial.print("Value 3: ");
  Serial.println(pH, 2);
  Serial.print("Value 4: ");
  Serial.println(TDS);
  Serial.print("Value 5: ");
  Serial.println(jam);
  Serial.print("Value 6: ");
  Serial.println(menit);
  Serial.print("Value 7: ");
  Serial.println(detik);
  Serial.print("eDO: ");
  Serial.println(errorDO);
  Serial.print("dDO: ");
  Serial.println(derrorDO);

  listen = false;
}
