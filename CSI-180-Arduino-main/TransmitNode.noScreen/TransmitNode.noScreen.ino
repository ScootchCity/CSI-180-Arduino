//DHT11 library
#include "DHT.h"
//DHT11 data pin connection and sensor type
#define DHTPIN 8
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

//RF library https://github.com/PaulStoffregen/RadioHead/blob/master/RH_ASK.h

//RH_ASK setup
#include <RH_ASK.h>
#ifdef RH_HAVE_HARDWARE_SPI
#include <SPI.h> // Not actually used but needed to compile
#endif
//RH Driver
//(data rate, recieve pin, transmit pin, 0)
RH_ASK driver(2000, 12, 9, 0);

#define NODE_ID 0;

void setup() {
  Serial.begin(9600);
  Serial.println("STARTING...");
  
  //start the sensor
  dht.begin();

  //Check driver is init -> need to understand this (pulled from RH_ASK example)
  if (!driver.init())
#ifdef RH_HAVE_SERIAL
      Serial.println("init failed");
#else
	;
#endif
}

void loop() {
 
}

float getTemp() {return dht.readTemperature();}
float getHumid() {return dht.readHumidity();}

char formatDataLine(float temp, float humid) {
  char *returnLine = "test";
  //FOR DEBUG
  Serial.println("formatdataLine: ");
  Serial.println(returnLine);
  return returnLine;
}

void sendData(float temp, float humid) {
  char *dataLine = formatDataLine(temp,humid);
  driver.send((uint8_t *)dataLine, strlen(dataLine));
  driver.waitPacketSent();
  delay(500);
  //FOR DEBUG
  Serial.println("sent...");
  Serial.println(dataLine);
}

//https://www.airspayce.com/mikem/arduino/RadioHead/classRH__ASK.html#a5cf896776548ec88b13a880d2e1f65ba
const uint8_t DATA_ARRAY_LENGTH = 2;

void sendData2(const float in) {
  int8_t digit = 0, decimal = 0;
  int8_t *dataLine;
  dataLine[0] = digit;
  dataLine[1] = decimal;
  formatData(in, digit, decimal);
  driver.send(dataLine, DATA_ARRAY_LENGTH);
  driver.waitPacketSent();
  //FOR DEBUG
  Serial.println("sent...");
  Serial.println(dataLine[0]);
  Serial.println(dataLine[1]);
}

void formatData(const float in, int8_t& digit, int8_t& decimal) {
    digit = in;
    decimal = (in - digit) * 100;
}