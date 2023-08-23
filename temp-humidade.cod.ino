// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

// The current code is based in exemple from the library and modificated to integrate a display, a LED RGB and a button

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor
#include <Adafruit_Sensor.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

LiquidCrystal_I2C lcd(0x3F,16,2);

#define DHTPIN 5     // Digital pin connected to the DHT sensor
#define red 4
#define green 3
#define blue 2

#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321


DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  Serial.println(F("DHTxx test!"));

  dht.begin();

lcd.init();  // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Temp");
  lcd.setCursor(7, 0);
  lcd.print("|humidade");

  // led RGB
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(blue,OUTPUT);
  
}

void loop() {
  // Wait a few seconds between measurements.
  delay(1000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));

 // display temperature and humidity
  lcd.setCursor(0,1);
  lcd.print(hic);
  lcd.setCursor(6,1);
  lcd.print("C|");
  lcd.setCursor(8,1);
  lcd.print(h);
  lcd.setCursor(13,1);
  lcd.print("%");

  ledON(hic);
 
}

void ledON(float temp) // change LED's color based on temperature
{
  if (temp >= 35){   
    offled();
    digitalWrite(red, HIGH);
    }
  else if (temp >= 20){
    offled();
    digitalWrite(green, HIGH);
    }
  else {
    offled();
    digitalWrite(blue, HIGH);
    }
}

void offled() // turn all the LEDs off
{
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);
  digitalWrite(blue, LOW);
}