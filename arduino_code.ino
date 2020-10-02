// Arduino UNO watering system

const int soilMoisturePin = A0;  //why int??
const int water_tank = 2    ;   //why int??
float soilMoistureRaw = 0; //Raw analog input of soil moisture sensor (volts)
int percentageHumidity = 0;
const int watering_time = 5000; //measured in ms
const int watering_thrashhold = 50;

const int dry = 697;  // value for dry sensor
const int wet = 339; // value for wet sensor

bool watering = false;
bool watered_today = false;

void setup()
{ 
  Serial.begin(9600);
  
  if (! rtc.initialized()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    Serial.print(now())
  time = rtc.now
}

void loop()
{
  //Reset wateredToday variable if it's a new day
  if (!(time.day()==rtc.day())) { 
    wateredToday = false;
  }
  
  
  soilMoistureRaw = analogRead(soilMoisturePin);

  percentageHumidity = map(soilMoistureRaw, wet, dry, 100, 0); // More info: https://www.arduino.cc/reference/en/language/functions/math/map/

  if ((percentageHumidity < watering_thrashhold) and (watered_today = false) and (rtc.hour() > 08) and (rtc.hour() < 10){

    digitalWrite(water_tank, HIGH);
    delay(watering_time);
    digitalWrite(water_tank, LOW);
    watering = true;
    time = rtc.now
  }

  else {
    

    Serial.print("watered today = ");
    Serial.print(watered_today); // possible?
    Serial.print(time);
    delay(250)
  }

  Serial.print("(");
  Serial.print(soilMoistureRaw);
  Serial.print(")---");
  Serial.print(percentageHumidity);
  Serial.println("%");  //difference between print and println
  
  delay(250);
}
