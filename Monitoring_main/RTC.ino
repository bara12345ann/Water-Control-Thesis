char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void DS3231_begin() {
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    //rtc.adjust(DateTime(2023, 7, 28, 20, 29, 0));
  }

  // When time needs to be re-set on a previously configured device, the
  // following line sets the RTC to the date & time this sketch was compiled
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // This line sets the RTC with an explicit date & time, for example to set
  // January 21, 2014 at 3am you would call:
  // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
}

String DS3231_read() {
  DateTime now = rtc.now();

  String bulan = String(now.month());
  String hari = String(now.day());
  String jam = String(now.hour());
  String menit = String(now.minute());
  String detik = String(now.second());

  String waktu, waktu_tgl;
  
  if (bulan.length() < 2) {
    waktu_tgl += "0";
  }
  waktu_tgl += bulan + "-";

  if (hari.length() < 2) {
    waktu_tgl += "0";
  }
  waktu_tgl += hari;

  if (jam.length() < 2) {
    waktu += "0";
  }
  waktu += jam + ":";

  if (menit.length() < 2) {
    waktu += "0";
  }
  waktu += menit + ":";

  if (detik.length() < 2) {
    waktu += "0";
  }
  waktu += detik;

  String mission_time = String(now.year()) + "-" + waktu_tgl + " " + waktu;
  Timestamp = jam + "," + menit + "," + detik;
  return mission_time;
}
