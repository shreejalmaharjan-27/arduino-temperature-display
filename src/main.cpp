#include <Arduino.h>
#include <Adafruit_SH1106.h>
#include <Adafruit_GFX.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SPI.h>


// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 2
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

#define OLED_RESET 4
Adafruit_SH1106 display(OLED_RESET);



void setup(void)
{
  Serial.begin(9600);
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setTextSize(3);

  Serial.println("Arduino Digital Temperature // Serial Monitor Version"); //Print a message
  sensors.begin();

}

void loop(void)
{
  sensors.requestTemperatures();  

  float temp = sensors.getTempCByIndex(0);
  char deg = 248;

  String str;
  String console;

  str+= String(temp);
  str+= deg;
  str+="C";

  console += "Temperature is ";
  console += String(temp);
  console += " celcius";



  Serial.println(console);

  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextColor(WHITE);
  display.setTextSize(3);
  display.println(str);

  display.display();
  delay(1000);
}