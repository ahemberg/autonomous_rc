/*
 * Code snippet for controlling the engines using a Toshiba 6612 dual H-bridge
 */

// Engine pins
#define AIN1 2
#define BIN1 8
#define AIN2 7
#define BIN2 12
#define PWMA 3
#define PWMB 5
#define STBY 4

#define MOTOR 'A'
#define SERVO 'B'

#define MAX_LEFT 700
#define MAX_RIGHT 620


// Control
#define SERVO_MEAS A0

void disable_engines() {
  digitalWrite(STBY, LOW);
}

void enable_engines() {
  digitalWrite(STBY, HIGH);
}


void run_cw(char engine, int eng_speed) {
  int in1, in2, pwm;
  if (engine == MOTOR) {
    in1 = AIN1;
    in2 = AIN2;
    pwm = PWMA;
  } else if (engine == SERVO) {
    in1 = BIN1;
    in2 = BIN2;
    pwm = PWMB;
  }

  enable_engines();

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(pwm, eng_speed);
  
}


void run_ccw(char engine, int eng_speed) {
  
  int in1, in2, pwm;
  if (engine == 'A') {
    in1 = AIN1;
    in2 = AIN2;
    pwm = PWMA;
  } else if (engine == 'B') {
    in1 = BIN1;
    in2 = BIN2;
    pwm = PWMB;
  }

  enable_engines();

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(pwm, eng_speed);
}

void stop_servo() {
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
  digitalWrite(PWMB, HIGH);
}


void break_engine() {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  digitalWrite(PWMA, HIGH);
}
void stopAtObstacle(){
}

void drive_forward(int drive_speed) {
  run_cw(MOTOR, drive_speed);
}

void drive_backward(int drive_speed) {
  run_ccw(MOTOR, drive_speed);
}

void turn_left(int turn_speed){
  run_cw(SERVO, turn_speed);
}

void turn_right(int turn_speed){
  run_ccw(SERVO, turn_speed);
}

void full_left(int turn_speed) {
  if(!overshoot_left()){
    turn_left(turn_speed);
  }
}

void full_right(int turn_speed) {
  if(!overshoot_right()){
    turn_right(turn_speed);
  }
}

bool overshoot_servo() {
  return overshoot_left() || overshoot_right();
}

bool overshoot_left() {
  return measure_angle() > MAX_LEFT;
}

bool overshoot_right() {
  return measure_angle() < MAX_RIGHT;
}

int measure_angle() {
  return analogRead(SERVO_MEAS);
}

String command;
bool input;
void serialEvent() {
  while (Serial.available()) {
      command = Serial.readString();
      break;
  }
  input = true;
}

void setup() {
  pinMode(AIN1, OUTPUT); 
  pinMode(AIN2, OUTPUT); 
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);  
  pinMode(BIN2, OUTPUT); 
  pinMode(PWMB, OUTPUT); 
  pinMode(STBY, OUTPUT); 
  disable_engines();
  Serial.begin(9600);
  Serial.setTimeout(50);
}

bool start = true;


int motorspeed = 120;
int servospeed = 100;
void loop() {
  enable_engines();
  //Serial.println(measure_angle());

  input = false; 

//  Serial.println(command[0]);
  
  if (command[0] == 'w') {
     drive_forward(motorspeed);
  } else if (command[0] == 's') {
    break_engine();
  } else if (command[0] == 'a') {
    Serial.println("In a");
    if(overshoot_left()) {
      Serial.println("Overshoot a");
      stop_servo();
      command = "";
    } else {
      Serial.println("full left");
      full_left(servospeed);
    }
  } else if (command[0] == 'd') {
    if(overshoot_right()) {
      stop_servo();
      command = "";
    } else {
      full_right(servospeed);
    }
  }

  
  /*
  if(overshoot_right()) {
    full_left(30);
  }
  else if(overshoot_left()) {
    full_right(30);
  }
  else {
    if(start) {
      full_left(30);
    }
  }
  start = false;
  /*run_cw('A', 200);
 
  int angle = measure_angle();
  
  while (angle < 900) {
    angle = measure_angle();
    run_cw('B', 64);
    Serial.println(angle);
  }
  while (angle > 600) {
    angle = measure_angle();
    run_ccw('B', 64);
    Serial.println(angle);
  }
  */
}
