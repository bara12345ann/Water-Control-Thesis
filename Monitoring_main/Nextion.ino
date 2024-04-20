void nextion_data(){
  String display_data;
  display_data = "timertc.txt=\"" + DS3231_read() + "\"";
  Serial2.print(display_data);
  Serial2.write(0xff);
  Serial2.write(0xff);
  Serial2.write(0xff);

  display_data = "batt.txt=\"" + battery_read() + "\"";
  Serial2.print(display_data);
  Serial2.write(0xff);
  Serial2.write(0xff);
  Serial2.write(0xff);

  display_data = "tds.txt=\"" + tds_read() + "\"";
  Serial2.print(display_data);
  Serial2.write(0xff);
  Serial2.write(0xff);
  Serial2.write(0xff);

  display_data = "do.txt=\"" + do_read(temperature) + "\"";
  Serial2.print(display_data);
  Serial2.write(0xff);
  Serial2.write(0xff);
  Serial2.write(0xff);

  display_data = "ph.txt=\"" + pH_read() + "\"";
  Serial2.print(display_data);
  Serial2.write(0xff);
  Serial2.write(0xff);
  Serial2.write(0xff);

  display_data = "temp.txt=\"" + thermo_read() + "\"";
  Serial2.print(display_data);
  Serial2.write(0xff);
  Serial2.write(0xff);
  Serial2.write(0xff);

  display_data = "tempair.txt=\"" + dht_read_t() + "\"";
  Serial2.print(display_data);
  Serial2.write(0xff);
  Serial2.write(0xff);
  Serial2.write(0xff);

  display_data = "hum.txt=\"" + dht_read_h() + "\"";
  Serial2.print(display_data);
  Serial2.write(0xff);
  Serial2.write(0xff);
  Serial2.write(0xff);

  display_data = "wifi.txt=\"" + String("OK!!") + "\"";
  Serial2.print(display_data);
  Serial2.write(0xff);
  Serial2.write(0xff);
  Serial2.write(0xff);
}
