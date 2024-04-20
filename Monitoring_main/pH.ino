//butuh voltage devider untuk menurunkan 5v input
// R1 1k
// R2 1k

String pH_read(){
  uint16_t adc2;

  adc2 = ads.readADC_SingleEnded(2);
  float voltageOut = ads.computeVolts(adc2); //gausah dikasi voltage devider btw

  float pH_val = (18.478*voltageOut)-9.2693;//(need calibration) perlu fitur kalibrasi 
  // bikin tombol untuk kalibrasi, nnti ada tombol kalibrasi
  //pilihan ph buffer 4 dan 7, trs function linear regression di perbarui
  String pH_ = String(pH_val, 2);
  if (voltageOut < 0.2){
    pH_ = 3;
  }
  return pH_;
}
