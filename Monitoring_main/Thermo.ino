String thermo_read(){
  thermo.requestTemperatures();
  temperature = thermo.getTempCByIndex(0);
  String temp_ = String(temperature, 2);

  if(temperature < 0) 
  {
    temperature= 26;
    temp_ = 28;
  } 

  
  return (temp_);
}
