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

//OLED Defines from Adafruit ssd1306 example
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//Initialize DHT object
DHT dht(DHTPIN, DHTTYPE);


void setup() {
  Serial.begin(9600);
  Serial.println("STARTING...");
  //start the sensor
  dht.begin();

  //FROM ADAFRUIT EXAPLE - MUST USE TO TURN ON SCREEN
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  initOLED();
  display.println(F("Starting..."));
  display.display();
  delay(2000);
}

void loop() {
  //Serial.println(getTemp());
  //Serial.println(getHumid());

  tempScreen();
  delay(5000);
  humidScreen();
  delay(5000);
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
