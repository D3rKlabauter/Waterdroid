// Arduino UNO watering system

const int soilMoisturePin = A0;  //why int??
const int water_tank = 2    ;   //why int??
float soilMoistureRaw = 0; //Raw analog input of soil moisture sensor (volts)
int percentageHumidity = 0;
const int watering_time = 500; //measured in ms
const int watering_thrashhold = 50;

const int dry = 704;  // value for dry sensor
const int wet = 339; // value for wet sensor
//bool watering = false;
bool watered_today = false;

void setup()
{ 
  Serial.begin(9600);
  pinMode(water_tank,OUTPUT);
  digitalWrite(water_tank, LOW);
}

void loop()
{
  
  //Reset wateredToday variable if it's a new day
  
  soilMoistureRaw = analogRead(soilMoisturePin);

  percentageHumidity = map(soilMoistureRaw, wet, dry, 100, 0); // More info: https://www.arduino.cc/reference/en/language/functions/math/map/

  if ((percentageHumidity < watering_thrashhold) and (watered_today == false)) {

      digitalWrite(water_tank, HIGH);
      delay(watering_time);
      digitalWrite(water_tank, LOW);
      watered_today = true;
      Serial.print("ON"); 
  }

  else {

    Serial.print("watered today = ");
    Serial.print(watered_today);
    Serial.print("OFF");
  }
  

  Serial.print("(");
  Serial.print(soilMoistureRaw);
  Serial.print(")---");
  Serial.print(percentageHumidity);
  Serial.println("%");  //difference between print and println
  
  delay(250);
}
