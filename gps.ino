#include <LiquidCrystal.h>
#include <TinyGPS.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
TinyGPS gps;  //Creates a new instance of the TinyGPS object

#define vibration_sen 8 


void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(vibration_sen, INPUT);
  lcd.setCursor(3,0);
  lcd.print("Project by");
   lcd.setCursor(2,1);
  lcd.print("Group F8");
  delay(1000);
  lcd.clear();
 
}

void loop()
{
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;
  int vibration = digitalRead(vibration_sen);

  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (Serial.available())
    {
      char c = Serial.read();
      //Serial.print(c);
      if (gps.encode(c)) 
        newData = true;  
    }
  }

if(vibration == HIGH) {
  if (newData)      //If newData is true
  {
    lcd.clear();
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age); 
    ////String lat=(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);  
    //String lon=(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    lcd.setCursor(0,0);
    lcd.print("Lat= ");
    lcd.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    lcd.setCursor(0,1);
    lcd.print("Lon= ");
    lcd.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    
    

  }
}
 
  Serial.println(failed);
 // if (chars == 0)
   // Serial.println("** No characters received from GPS: check wiring **");
}
