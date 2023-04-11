void readSensor() {
  float voltPZEM = pzem.voltage();
  float currentPZEM = pzem.current();
  float powerPZEM = pzem.power();
  float energyPZEM = pzem.energy();

  //  if (bufferPZEM > powerPZEM && abs(bufferPZEM - powerPZEM) >= 3 ) {
  //    countLamp--;
  //    bufferPZEM = powerPZEM;
  //  }
  //  else if (bufferPZEM < powerPZEM && abs(bufferPZEM - powerPZEM) >= 3) {
  //    countLamp++;
  //    bufferPZEM = powerPZEM;
  //  }
  //  if (countLamp < 0) {
  //    countLamp = 0;
  //  }

  countLamp = powerPZEM / dayaperLampu;
  bufferPZEM = (int)powerPZEM % dayaperLampu;

  if (bufferPZEM >= dayaperLampu / 2) {
  countLamp++;
}

//  dataPZEM[0] = String(voltPZEM) + '#' + String(currentPZEM) + '#' + String(powerPZEM) + '#' + String(energyPZEM) + '#' + String(countLamp);

if (isnan(voltPZEM)) {
    allDataSensor[0][0] = 0;
    allDataSensor[0][1] = 0;
    allDataSensor[0][2] = 0;
    allDataSensor[0][3] = 0;
  }
  else {
    allDataSensor[0][0] = voltPZEM;
    allDataSensor[0][1] = currentPZEM;
    allDataSensor[0][2] = powerPZEM;
    allDataSensor[0][3] = energyPZEM;
  }
  allDataSensor[0][4] = 0;

  if (flagSPIFFS >= 100) {
  writeSPIFFS("/datalogging.txt", String(allDataSensor[0][0]) + "," + String(allDataSensor[0][1]) + "," + String(allDataSensor[0][2]) + "," + String(allDataSensor[0][3]) + "," + String(allDataSensor[0][4]) + "," + String(countLamp) + "," + String(allDataSensor[0][5]));
    writeSPIFFS("/datarelay.txt", String(allDataSensor[0][5]) + "," + String(flagSPIFFS));
    //    readSPIFFS("/datalogging.txt");
    flagSPIFFS = 0;
  }
  else {
    appendSPIFFS("/datalogging.txt", String(allDataSensor[0][0]) + "," + String(allDataSensor[0][1]) + "," + String(allDataSensor[0][2]) + "," + String(allDataSensor[0][3]) + "," + String(allDataSensor[0][4]) + "," + String(countLamp) + "," + String(allDataSensor[0][5]));
    writeSPIFFS("/datarelay.txt", String(allDataSensor[0][5]) + "," + String(flagSPIFFS));
    //    readSPIFFS("/datalogging.txt");
    flagSPIFFS++;
  }

  //  for (int i = 0; i < 5; i++) {
  //    Serial.println(allDataSensor[0][i]);
  //  }
}
