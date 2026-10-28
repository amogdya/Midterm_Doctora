const int OUT = 2;     
const int OUT1 = 35;     // IR Proximity Sensor pin
const int RST = 34;
int reset = 0;
int Number_of_Object = 0;   // Counter for objects
int SensorState = 0;        // Current sensor reading
int SensorState_1 =0;
int lastSensorState = HIGH; // Previous sensor reading
int lastSensorState_1 = HIGH;
const int LED_10s[7] = {32, 33, 25, 26, 27, 14, 13};
const int LED_1s[7]  = {19, 18, 5, 17, 16, 4, 22};


void setup() {
  Serial.begin(115200);
  pinMode(OUT, INPUT);
  pinMode(RST, INPUT_PULLDOWN);
  pinMode(OUT1, INPUT);
  for(int i = 0; i < 7; i++){
    pinMode(LED_10s[i], OUTPUT);
    pinMode(LED_1s[i], OUTPUT);
  }
}
#include "Decode.h"

void loop() {
  SensorState = digitalRead(OUT);
  SensorState_1 = digitalRead(OUT1);
  reset = digitalRead(RST);

 if(reset==LOW){
  Number_of_Object=7;
 }
 else{
    if (SensorState == LOW && lastSensorState == HIGH) {
    Number_of_Object++;
    
    if(Number_of_Object > 99) {
      Number_of_Object = 0;
    }
    
    Serial.print("Object detected! Total: ");
    Serial.println(Number_of_Object);
    
    delay(200); 
  }
  if(SensorState_1== LOW && lastSensorState_1 == HIGH){
    if(Number_of_Object>0){
      Number_of_Object--;
    }
    Serial.print("Object detected! Total:");
    Serial.println(Number_of_Object);
    delay(200);
  }
 }

  decode(Number_of_Object);
  display();
  
  lastSensorState = SensorState;
}