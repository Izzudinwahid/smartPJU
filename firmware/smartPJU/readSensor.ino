void readSensor() {
  float voltPZEM = pzem.voltage();
  float currentPZEM = pzem.current();
  float powerPZEM = pzem.power();
  float energyPZEM = pzem.energy();

  if (isnan(voltPZEM)) {
    Serial.println("Error reading voltage");
  } else if (isnan(currentPZEM)) {
    Serial.println("Error reading current");
  } else if (isnan(powerPZEM)) {
    Serial.println("Error reading power");
  } else if (isnan(energyPZEM)) {
    Serial.println("Error reading energy");
  }
  else {

    // Print the values to the Serial console
    Serial.print("Voltage: ");      Serial.print(voltPZEM);      Serial.println("V");
    Serial.print("Current: ");      Serial.print(currentPZEM,4);      Serial.println("A");
    Serial.print("Power: ");        Serial.print(powerPZEM);        Serial.println("W");
    Serial.print("Energy: ");       Serial.print(energyPZEM, 3);     Serial.println("kWh");
  }
}
