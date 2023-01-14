#include <Arduino.h>
#include <Adafruit_SH1106.h>
#include <Adafruit_GFX.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SPI.h>
#include <SoftwareSerial.h>


// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 2
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

#define OLED_RESET 4


Adafruit_SH1106 display(OLED_RESET);

// send data on pin 9 & 8
SoftwareSerial ATDevice(9,8); // tx rx
String command(const char *toSend, unsigned long milliseconds, boolean ret);

void setup(void)
{

  // begin serial console
  Serial.begin(9600);
  ATDevice.begin(9600);

  // initialize display
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);

  // display Adafruit splash screen
  display.display();
  delay(2000);

  display.clearDisplay();
  display.setTextSize(3);

  Serial.println("Arduino Digital Temperature"); //Print a message


  // start sensors
  sensors.begin();

  // start script1.lua
  command("dofile('script1.lua')", 1000, false);

}

void loop(void)
{
  String str;
  String console;

  sensors.requestTemperatures();  

  float temp = sensors.getTempCByIndex(0);


  // This is the ASCII code for Degree symbol `°` 
  char deg = 248;

  // string for displaying on the OLED Screen
  str += String(sensors.getTempCByIndex(0));
  str += deg;
  str += "C";

  display.clearDisplay();
  display.setCursor(0,0); 
  display.setTextColor(WHITE);
  display.setTextSize(3);
  display.println(str); // set string to display on oled screen

  // display the string
  display.display();  


  // string for displaying on the Serial console
  console += "Temperature is ";
  console += String(temp);
  console += " celcius";

  // print to console
  Serial.println(console);

  // use the same variable to generate setTemp function
  console = "";
  console += "setTemp('";
  console += String(temp);
  console += "')";

  // execute the function
  command(console.c_str(), 1000, false);

  delay(2000);
}

String command(const char *toSend, unsigned long milliseconds, boolean ret) {
  String result;
  if (ret) {
    Serial.print("Sending: ");
    Serial.println(toSend);
  }
  ATDevice.println(toSend);

  if (ret) {
      unsigned long startTime = millis();
      Serial.print("Received: ");
      while (millis() - startTime < milliseconds) {
        if (ATDevice.available()) {
          char c = ATDevice.read();
          Serial.write(c);
          result += c;  // append to the result string
        }
      }
    Serial.println();  // new line after timeout.
  }
    return result;
}