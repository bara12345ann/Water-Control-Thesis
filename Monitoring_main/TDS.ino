
String tds_read() {
  int16_t adc0;

  adc0 = ads.readADC_SingleEnded(0);
  float voltage = ads.computeVolts(adc0);

  int tdsValue=(133.42*voltage*voltage*voltage - 255.86*voltage*voltage + 857.39*voltage)*0.5;

  return String(tdsValue);
}
