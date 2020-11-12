// Arduino UNO watering system


#include "GravityRtc.h"
#include "Wire.h"

GravityRtc rtc;     //RTC Initialization

const int soilMoisturePin = A0;  //why int??
const int water_tank = 2    ;   //why int??
const int powersupply = 12; // just for testing

float soilMoistureRaw = 0; //Raw analog input of soil moisture sensor (volts)
int percentageHumidity = 0;

const int watering_time = 5000; //measured in ms
const int watering_thrashhold = 50;

const int dry = 697;  // value for dry sensor
const int wet = 339; // value for wet sensor

//bool watering = false;
bool watered_today = false;

void setup()
{
  Serial.begin(9600);
  pinMode(water_tank,OUTPUT);
  pinMode(powersupply,OUTPUT); // just for testing
  
  digitalWrite(Volt, HIGH); // just for testing

  rtc.setup();
  //Set the RTC time automatically: Calibrate RTC time by your computer time
  rtc.adjustRtc(F(__DATE__), F(__TIME__));
  
  water_clock = rtc.now
}

void loop()
{
  //Reset wateredToday variable if it's a new day
  if (!(water_clock.day()==rtc.day())) { 
    wateredToday = false;
  }
  
  
  soilMoistureRaw = analogRead(soilMoisturePin);

  percentageHumidity = map(soilMoistureRaw, wet, dry, 100, 0); // More info: https://www.arduino.cc/reference/en/language/functions/math/map/

  if ((percentageHumidity < watering_thrashhold) and (watered_today = false)){

    digitalWrite(water_tank, HIGH);
    delay(watering_time);
    digitalWrite(water_tank, LOW);
    wateredToday = true;
    water_clock = rtc.now;
  }

  else {
    

    Serial.print("watered today = ");
    Serial.print(watered_today); // possible?
    delay(250)
  }

  Serial.print("(");
  Serial.print(soilMoistureRaw);
  Serial.print(")---");
  Serial.print(percentageHumidity);
  Serial.println("%");  //difference between print and println
  
  delay(250);
}
