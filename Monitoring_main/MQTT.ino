void mqtt_begin() {
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
    //mqttClient.subscribe("kontrol");
  }
  //mqttClient.setCallback(callback);
  String display_data = "wifi.txt=\"" + String("OK!!") + "\"";
  Serial2.print(display_data);
  Serial2.write(0xff);
  Serial2.write(0xff);
  Serial2.write(0xff);
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}

void connectToWiFi() {
  WiFi.setTxPower(WIFI_POWER_19_5dBm);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
    String display_wifi = "wifi.txt=\"" + String("...") + "\"";
    Serial2.print(display_wifi);
    Serial2.write(0xff);
    Serial2.write(0xff);
    Serial2.write(0xff);
  }
  Serial.println("Connected to WiFi");
  digitalWrite(led2, HIGH);
}

void publishMessage(const char* message) {
  String dummy = suhu_w + "," + do_ + "," + ph_ + "," + Timestamp;
  const char* convertedStr = dummy.c_str();
  
  String mqtt_clientId = "mesh_gateway-";
  mqtt_clientId += String(random(0xffff), HEX);

    if (mqttClient.connect("ESP8266Client", "bara", mqttPassword)) {
      Serial.print("Hai");
      if(data1 == false){
      mqttClient.publish(pubTopic, convertedStr);
      Serial.println("Data0 published");
      }else{
      mqttClient.publish(pubTopic, message,true);
      Serial.println("Message published");
      }
      data1 = true;
      mqttClient.disconnect();
    }

}
