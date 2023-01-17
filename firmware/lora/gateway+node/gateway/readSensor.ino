void readSensor() {
  float voltPZEM = pzem.voltage();
  float currentPZEM = pzem.current();
  float powerPZEM = pzem.power();
  float energyPZEM = pzem.energy();

  if (bufferPZEM > powerPZEM && abs(bufferPZEM - powerPZEM) >= 3 ) {
    countLamp--;
    bufferPZEM = powerPZEM;
  }
  else if (bufferPZEM < powerPZEM && abs(bufferPZEM - powerPZEM) >= 3) {
    countLamp++;
    bufferPZEM = powerPZEM;
  }
  if (countLamp < 0) {
    countLamp = 0;
  }

  //  dataPZEM[0] = String(voltPZEM) + '#' + String(currentPZEM) + '#' + String(powerPZEM) + '#' + String(energyPZEM) + '#' + String(countLamp);
  
  allDataSensor[0][0] = voltPZEM;
  allDataSensor[0][1] = currentPZEM;
  allDataSensor[0][2] = powerPZEM;
  allDataSensor[0][3] = energyPZEM;
  allDataSensor[0][4] = countLamp;

//  for (int i = 0; i < 5; i++) {
//    Serial.println(allDataSensor[0][i]);
//  }
}
