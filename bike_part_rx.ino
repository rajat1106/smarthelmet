
#include <VirtualWire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 7, 8, 9, 10);
   
int count;
const int buz = 4;
const int mt = 3;
String motor="";
String helmet="";
String alcohol="";
int vs = 6;
int shockVal = HIGH;
void setup()
{   
    pinMode(mt,OUTPUT);
    pinMode(buz,OUTPUT);
    lcd.begin(16, 2); 
   
    
    vw_set_rx_pin(5);       //Sets pin D12 as the RX Pin
    //vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(4000);       // Bits per sec
    vw_rx_start();       // Start the receiver PLL running
    
    lcd.setCursor(0, 0);
    lcd.print("Smart bike");
    lcd.setCursor(0, 1);
    lcd.print("   helmet");
    digitalWrite(buz,HIGH);
    digitalWrite(mt,LOW);
    delay(1000);
    lcd.clear();
}
void loop()
{    
   
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;
    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
     int i;
            for (i = 0; i < buflen; i++)
            {
            char c = (buf[i]);
            Serial.print(c);
            Serial.print(" ");   
      
    if (buf[i] =='0')
    {
    digitalWrite(mt,HIGH);
    digitalWrite(buz,LOW);
    }
    if (buf[i] =='1')
    {  
    digitalWrite(mt,LOW);
    digitalWrite(buz,HIGH);
   }
   if (buf[i] =='2')
   {
    alcohol="ALCOHOL DETECTED";
   }
   if (buf[i] =='3')
   {
      alcohol="   NO ALCOHOL    ";
   }
   if (buf[i] =='4')
   {
      helmet="HEL-IN";
   }
   if (buf[i] =='5')
   {
     helmet="HEL-NO"; 
   }

  
    if(digitalRead(mt)==HIGH)
    {
    motor="ENG- ON"; 
    }
    if(digitalRead(mt)==LOW)
    {
    motor="ENG-OFF"; 
    }
    
   lcd.setCursor(0,0);
   lcd.print(motor);
   lcd.setCursor(9,0);
   lcd.print(helmet);
   lcd.setCursor(0,1);
   lcd.print(alcohol);
   }    
   }
   }
