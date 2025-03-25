//DHT11 library
#include "DHT.h"

//OLED libraries from Adafruit ssd1306 example
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//DHT11 data pin connection and sensor type
#define DHTPIN 8
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

//OLED Defines from Adafruit ssd1306 example
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C //changed for the copy screens i have
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//RF Stuff https://github.com/pouriap/TinyRF
//Actual RF library https://github.com/PaulStoffregen/RadioHead/blob/master/RH_ASK.h

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

  //FROM ADAFRUIT EXAPLE - MUST USE TO TURN ON SCREEN
  //SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  /*
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  initOLED();
  display.println(F("Starting..."));
  display.display();
  delay(2000);
  */
}

void loop() {
  //Serial.println(getTemp());
  //Serial.println(getHumid());

  /*
  tempScreen();
  delay(5000);
  humidScreen();
  delay(5000);
  */

  sendData(getTemp(),getHumid());
  delay(500);
}

float getTemp() {return dht.readTemperature();}
float getHumid() {return dht.readHumidity();}

void initOLED() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
}
void tempScreen() {
  initOLED();
  display.println(F("Temperature:""\n\n"));
  display.setTextSize(4);
  display.print(getTemp(), 0);
  display.write(char(247));
  display.print("C");
  display.display();
}
void humidScreen() {
  initOLED();
  display.println(F("Humidity:\n\n"));
  display.setTextSize(4);
  display.print(getHumid(), 1);
  display.print("%");
  display.display();
}

char formatDataLine(float temp, float humid) {
  char returnLine = NODE_ID + temp + humid;
  Serial.println("formatdataLine: ");
  Serial.println(returnLine);
  return returnLine;
}

void sendData(float temp, float humid) {
  //const char *dataLine = "bweh";
  char *dataLine = "test";
  driver.send((uint8_t *)dataLine, strlen(dataLine));
  driver.waitPacketSent();
  delay(500);
  Serial.println("sent...");
  Serial.println(dataLine);
}
