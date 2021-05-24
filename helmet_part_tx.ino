
#include <VirtualWire.h>
const int sw=1; // FSR SENSOR
int adc=0; // ALCOhOL SENSOR
void setup()
{
    pinMode(sw, INPUT);
    vw_set_tx_pin(12);          // Sets pin D13 as the TX pin // RF TRANSMITTER PART
   // vw_set_ptt_inverted(true);  // Required for DR3100
    vw_setup(4000);         // Bits per sec
}

void loop()
{  
  const char *msg0 = "0";
  const char *msg1 = "1";
  const char *msg2 = "2";
  const char *msg3 = "3";
  const char *msg4 = "4";
  const char *msg5 = "5";
  
  float adcValue=0;
  for(int i=0;i<10;i++)
  {
    adcValue+= analogRead(A0);
    delay(10);
  }
    float v= (adcValue/10) * (5.0/1024.0);
    float adc= 0.67 * v;
  
 
  if (adc<0.7&&digitalRead(sw)==HIGH) 
  {
    vw_send((uint8_t *)msg0, strlen(msg0));    
    vw_wait_tx(); 
    delay(30); }   
    else                                            
    {
    vw_send((uint8_t *)msg1, strlen(msg1));     
    vw_wait_tx();
    } 

 if (adc>0.7) 
{
  vw_send((uint8_t *)msg2, strlen(msg2));    
  vw_wait_tx(); 
  delay(30); } 
 if (adc<0.7)                                          
 {
  vw_send((uint8_t *)msg3, strlen(msg3));     
  vw_wait_tx();
 } 
 
if (digitalRead(sw)==HIGH) 
{
  vw_send((uint8_t *)msg4, strlen(msg4));    
  vw_wait_tx(); 
  delay(30); } 
 if (digitalRead(sw)==LOW)                                          
 {
  vw_send((uint8_t *)msg5, strlen(msg5));     
  vw_wait_tx();
 } 
  }
