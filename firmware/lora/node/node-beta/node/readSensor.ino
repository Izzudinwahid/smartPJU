void readSensor() {
  float voltPZEM = pzem.voltage();
  float currentPZEM = pzem.current();
  float powerPZEM = pzem.power();
  float energyPZEM = pzem.energy();

  // Print the values to the Serial console
  //  Serial.println(bufferPZEM);
  //  Serial.println(powerPZEM);
  //  Serial.println(abs(bufferPZEM - powerPZEM));
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
  dataSensor[0] = String(voltPZEM) + '#' + String(currentPZEM) + '#' + String(powerPZEM) + '#' + String(energyPZEM) + '#' + String(countLamp)+ '#' + String(statusRelay);
  Serial.println(dataSensor[0]);
}
