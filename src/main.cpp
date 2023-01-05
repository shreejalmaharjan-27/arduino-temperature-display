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

  // begin serial console
  Serial.begin(9600);

  // initialize display
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);

  // display Adafruit splash screen
  display.display();
  delay(2000);

  display.clearDisplay();
  display.setTextSize(3);

  Serial.println("Arduino Digital Temperature // Serial Monitor Version"); //Print a message

  // start sensors
  sensors.begin();

}

void loop(void)
{
  sensors.requestTemperatures();  

  float temp = sensors.getTempCByIndex(0);

  // This is the ASCII code for Degree symbol `°` 
  char deg = 248;

  String str;
  String console;

  // string for displaying on the OLED Screen
  str += String(temp);
  str += deg;
  str +="C";

  // string for displaying on the Serial console
  console += "Temperature is ";
  console += String(temp);
  console += " celcius";

  // print to console
  Serial.println(console);

  display.clearDisplay();
  display.setCursor(0,0); 
  display.setTextColor(WHITE);
  display.setTextSize(3);
  display.println(str); // set string to display on oled screen

  // display the string
  display.display();

  // update data every 1 second
  delay(1000);
}