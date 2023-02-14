//#include <SoftwareSerial.h>
#include <String.h>
//#include <DHT.h>

//#define DHTPIN 5

//SoftwareSerial Serial2(15, 14);               //Serial Serial2 pin
//DHT dhtSensor(DHTPIN, DHT22);
String Write_API_key = "R91FECV1OAXG5QJN";  //Thingspeak Write API Key
String apn = "3gprs";
float kelembaban;
float suhu;
void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, 14, 15);
  //  Serial2.begin(9600);
  //  dhtSensor.begin();
  Serial.println("Serial2 GPRS Test");
  delay(2000);
}

void loop() {
  SetupModule();
  Serial2.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");
  delay(3000);
  ShowSerialData();

  Serial2.println("AT+CIPSEND");
  delay(2000);
  Serial.println();
  ShowSerialData();
  //  ReadSensor();
  String str = "GET https://api.thingspeak.com/update?api_key=" + Write_API_key + "&field1=" + String(1100) ;
  Serial.println(str);  delay(2000);
  Serial2.println(str); delay(4000);
  ShowSerialData();

  Serial2.println((char)26); delay(4000);
  Serial2.println();
  ShowSerialData();
  Serial2.println("AT+CIPSHUT");//close the connection
  delay(500);
  ShowSerialData();
  str = "";

  //total delay looping 50s
  delay(10000); //add 10s for 60s total delay looping
}

//void ReadSensor() {
//  kelembaban = dhtSensor.readHumidity();
//  suhu = dhtSensor.readTemperature();
//  delay(500);
//  Serial.println();
//  Serial.print("Temperature = "); Serial.print(suhu); Serial.print(" °C");
//  Serial.print("\t");
//  Serial.print("Humidity = "); Serial.print(kelembaban); Serial.println(" %");
//
//}

void SetupModule() {
  if (Serial2.available())Serial.write(Serial2.read());
  Serial2.println("AT"); delay(1000);
  Serial2.println("AT+CPIN?"); delay(1000);
  Serial2.println("AT+CREG?"); delay(1000);
  Serial2.println("AT+CGATT?"); delay(1000);
  Serial2.println("AT+CIPSHUT"); delay(1000);
  Serial2.println("AT+CIPSTATUS"); delay(2000);
  Serial2.println("AT+CIPMUX=0");  delay(2000);

  //setting the APN,
  Serial2.println("AT+CSTT=\"" + apn + "\""); delay(1000);
  ShowSerialData();
  Serial2.println("AT+CIICR");    delay(2000);
  ShowSerialData();

  //get local IP adress
  Serial2.println("AT+CIFSR");    delay(2000);
  ShowSerialData();

  Serial2.println("AT+CIPSPRT=0"); delay(2000);
  ShowSerialData();
}

void ShowSerialData() {
  while (Serial2.available() != 0)
    Serial.write(Serial2.read());
  delay(2000);
}
