const uint16_t DO_Table[41] = {
  14460, 14220, 13820, 13440, 13090, 12740, 12420, 12110, 11810, 11530,
  11260, 11010, 10770, 10530, 10300, 10080, 9860, 9660, 9460, 9270,
  9080, 8900, 8730, 8570, 8410, 8250, 8110, 7960, 7820, 7690,
  7560, 7430, 7300, 7180, 7070, 6950, 6840, 6730, 6630, 6400, 6330
};

String do_read(float temp) {
  int16_t adc3;

  adc3 = ads.readADC_SingleEnded(3);
  float voltage_mv = ads.computeVolts(adc3) * 1000;
  Serial.println("DO VOLT : " + String(voltage_mv));
  float temperatureDO = temp;
  if (temperatureDO <= 0){
    temperatureDO = 26;
  }

#if TWO_POINT_CALIBRATION == 0
  uint16_t V_saturation = (uint32_t)CAL1_V + (uint32_t)35 * temperatureDO - (uint32_t)CAL1_T * 35;
  Serial.println(temperatureDO);
  return String((voltage_mv * DO_Table[int(temperatureDO)] / V_saturation)/1000, 2);
  //return String(voltage_mv);
#else
  uint16_t V_saturation = (int16_t)((int8_t)temperatureDO - CAL2_T) * ((uint16_t)CAL1_V - CAL2_V) / ((uint8_t)CAL1_T - CAL2_T) + CAL2_V;
  return String((voltage_mv * DO_Table[int(temperatureDO)] / V_saturation)/1000, 2);
#endif
}
