void sendServer() {
  if (isnan(allDataSensor[flagidDevice][0])) {
    allDataSensor[flagidDevice][0] = 0;
    allDataSensor[flagidDevice][1] = 0;
    allDataSensor[flagidDevice][2] = 0;
    allDataSensor[flagidDevice][3] = 0;
  }

  Serial2.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
  ShowResponse(3000);

  Serial2.println("AT+SAPBR=3,1,\"APN\",\"internet\"");
  ShowResponse(3000);

  Serial2.println("AT+SAPBR=1,1");
  ShowResponse(5000);

  Serial2.println("AT+HTTPINIT");
  ShowResponse(5000);

  Serial.print("AT+HTTPPARA=");
  Serial.print('"');
  Serial.print("URL");
  Serial.print('"');
  Serial.print(',');
  Serial.print('"');
  Serial.print("http:");
  Serial.print('/');
  Serial.print('/');
  Serial.print("13.228.184.92/Insert.php?amr_id=");
  ///xxx is the api key

  Serial.print(amrId); //>>>>>>  variable 1 (temperature)
  Serial.print("&Kwh=");
  Serial.print(allDataSensor[flagidDevice][3]);
  Serial.print("&Arus=");
  Serial.print(allDataSensor[flagidDevice][1]);
  Serial.print("&Watt=");
  Serial.print(allDataSensor[flagidDevice][2]);
  Serial.print("&Tegangan=");
  Serial.print(allDataSensor[flagidDevice][0]);
  Serial.print("&Status=");
  Serial.print(statusRe);
  Serial.print("&Biaya=");
  Serial.print(biaya);
  Serial.print("&jumlah_lampu=");
  Serial.print(jumlahLampu);
  Serial.print("&lampu_hidup=");
  Serial.print(allDataSensor[flagidDevice][4]);
  Serial.print("&lampu_mati=");
  Serial.print(jumlahLampu - allDataSensor[flagidDevice][4]);
  Serial.print('"');
  Serial.write(0x0d);
  Serial.write(0x0a);



  Serial2.print("AT+HTTPPARA=");
  Serial2.print('"');
  Serial2.print("URL");
  Serial2.print('"');
  Serial2.print(',');
  Serial2.print('"');
  Serial2.print("http:");
  Serial2.print('/');
  Serial2.print('/');
  Serial2.print("13.228.184.92/Insert.php?amr_id=");
  ///xxx is the api key

  Serial2.print(amrId); //>>>>>>  variable 1 (temperature)
  Serial2.print("&Kwh=");
  Serial2.print(allDataSensor[flagidDevice][3]);
  Serial2.print("&Arus=");
  Serial2.print(allDataSensor[flagidDevice][1]);
  Serial2.print("&Watt=");
  Serial2.print(allDataSensor[flagidDevice][2]);
  Serial2.print("&Tegangan=");
  Serial2.print(allDataSensor[flagidDevice][0]);
  Serial2.print("&Status=");
  Serial2.print(allDataSensor[flagidDevice][5]);
  Serial2.print("&Biaya=");
  Serial2.print(biaya);
  Serial2.print("&jumlah_lampu=");
  Serial2.print(jumlahLampu);
  Serial2.print("&lampu_hidup=");
  Serial2.print(allDataSensor[flagidDevice][4]);
  Serial2.print("&lampu_mati=");
  Serial2.print(jumlahLampu - allDataSensor[flagidDevice][4]);
  Serial2.print('"');
  Serial2.write(0x0d);
  Serial2.write(0x0a);
  ShowResponse(3000);

  // set http action type 0 = GET, 1 = POST, 2 = HEAD
  Serial2.println("AT+HTTPACTION=1");
  GetResponse(10000);

  Serial2.println("AT+HTTPREAD");
  GetResponse(5000);               // respon di simpan kedalam variabel dataMasuk

  Serial.print("Full data :");
  Serial.println(dataMasuk);

  //  destinationFinal = parse(dataMasuk, '*', 0).toInt();
  //  flagPhase = parse(dataMasuk, '*', 1).toInt();
  //  statusRelay = parse(dataMasuk, '*', 2).toInt();
  //  //      timer = dataParse[3].toInt();
  //  HSBtimer = parse(dataMasuk, '*', 3).toInt() / 255;
  //  LSBtimer = parse(dataMasuk, '*', 3).toInt();
  //
  //  if (destinationFinal == 1) {
  //    if (statusRelay == 1) {
  //      digitalWrite(pinRelay, HIGH);
  //    }
  //    else {
  //      digitalWrite(pinRelay, LOW);
  //    }
  //    interval = dataParse[3].toInt() * 10;
  //    previousMillis = 0;
  //    delay(3000);
  //    readSensor();
  //  }
  //  else {
  //    sendMessage(dataParse[4]);
  //  }
  //
  //  String data0 = parse(dataMasuk, '*', 0);
  //  String data1 = parse(dataMasuk, '*', 1);
  //  String data2 = parse(dataMasuk, '*', 2);
  //
  //  Serial.println("--------------------------------------------------------------------");
  //
  //  Serial.print("data 0 :");
  //  Serial.println(data0);
  //
  //  Serial.print("data 1 :");
  //  Serial.println(data1);
  //
  //  Serial.print("data 2 :");
  //  Serial.println(data2);
  //
  //  Serial.println("--------------------------------------------------------------------");

  Serial2.println("AT+HTTPTERM");
  ShowResponse(3000);

  Serial2.println("AT+SAPBR=0,1");
  ShowResponse(5000);

}

void ShowResponse(int wait) {
  Serial.print("response : ");
  long timeNOW = millis();
  while (millis() - timeNOW < wait) {
    if (Serial2.find("OK")) {
      Serial.println("GOOD");
      return;
    }
    delay(10);
  }
  Serial.println("error time out");
}

void GetResponse(int wait) {
  dataMasuk = "";
  Serial.print("response : ");
  long timeNOW2 = millis();
  while (millis() - timeNOW2 < wait) {
    while (Serial2.available() > 0) {
      dataMasuk += (char)Serial2.read();
    }
    delay(1);
  }
  Serial.println(dataMasuk);
  Serial.println();
}


String parse(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
