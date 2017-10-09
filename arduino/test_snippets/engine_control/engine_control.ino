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

int measure_angle() {
  return analogRead(SERVO_MEAS);
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
}

void loop() {
  run_cw('A', 120);
  /*
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
