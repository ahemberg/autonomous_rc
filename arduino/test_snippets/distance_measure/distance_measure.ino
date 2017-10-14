#define TRIG 6
#define ECHO  9

void setup()  { 
   Serial.begin(9600); 
   pinMode(ECHO, INPUT); 
   pinMode(TRIG, OUTPUT);
   
 }
 
 void loop() { 
   digitalWrite(TRIG, HIGH); //Trigger ultrasonic detection 
   delayMicroseconds(100); 
   digitalWrite(TRIG, LOW); 
   int distance = pulseIn(ECHO, HIGH); //Read ultrasonic reflection
   Serial.println(distance); //Print distance 
} 

