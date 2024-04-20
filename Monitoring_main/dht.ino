String dht_read_h() {
  float h = sht31.readHumidity();
  return String(h, 1);
}

String dht_read_t() {
  float t = sht31.readTemperature();
  return String(t, 1);
}
