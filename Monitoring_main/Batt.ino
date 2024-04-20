// voltage devider
// R1 = 1k Ohm
// R2 = 2k2 Ohm
// bisa ditambahkan filter C

String battery_read(){
  int16_t adc1;

  adc1 = ads.readADC_SingleEnded(1);
  float voltageOut = ads.computeVolts(adc1);
  float percentage = ((voltageOut*(3200))/2200);
  /*
  percentage = map(percentage, 360, 420, 0, 100);
  if (percentage <= 0){
    percentage = 0;
  }else if (percentage >= 100){
    percentage = 100;
  }*/
  return String(percentage);
}
