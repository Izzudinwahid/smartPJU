void readSensor() {
  float voltPZEM = pzem.voltage();
  float currentPZEM = pzem.current();
  float powerPZEM = pzem.power();
  float energyPZEM = pzem.energy();

  // Print the values to the Serial console
  dataSensor[0] = String(voltPZEM) + '#' + String(currentPZEM) + '#' + String(powerPZEM) + '#' + String(energyPZEM);
}
