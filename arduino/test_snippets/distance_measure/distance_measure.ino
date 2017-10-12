 int inputPin=2; //ECHO pin 
 int outputPin=4; //TRIG pin 
 int inputPin2 = 7;
 int outputPin2 = 8;
 
 void setup() 
 { 
   Serial.begin(9600); 
   pinMode(inputPin, INPUT); 
   pinMode(outputPin, OUTPUT);
   pinMode(inputPin2, INPUT); 
   pinMode(outputPin2, OUTPUT); 
 }
 
 void loop() 
 { 
   digitalWrite(outputPin, HIGH); //Trigger ultrasonic detection 
   delayMicroseconds(100); 
   digitalWrite(outputPin, LOW); 
   int distance = pulseIn(inputPin, HIGH); //Read ultrasonic reflection
   //distance= distance/58; //Calculate distance 
   Serial.print(distance); //Print distance 
   Serial.print(",");

   digitalWrite(outputPin2, HIGH); //Trigger ultrasonic detection 
   delayMicroseconds(100); 
   digitalWrite(outputPin2, LOW);
   int distance2 = pulseIn(inputPin2, HIGH); //Read ultrasonic reflection
   //distance2= distance2/58; //Calculate distance 
   
   Serial.println(distance2); //Print distance 
   
 } 

