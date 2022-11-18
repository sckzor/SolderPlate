#include <max6675.h>

// Temperature Sensor
int thermoD0 = 12; // s0
int thermoCS = 15; 
int thermoCLK = 14; // sck
MAX6675 thermocouple(thermoCLK, thermoCS, thermoD0); 

int heatingElement = 16;

float setTemp;
float kP, kI, kD;

int running = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(heatingElement, OUTPUT);
  digitalWrite(heatingElement, HIGH);
}

int calcPID(float temp, float kp, float ki, float kd) {
  static float PID_prevError, currTime;
  float PID_value, PID_error, PID_p, PID_i, PID_d, elapsedTime, prevTime;
  
  PID_error = setTemp - temp + 3;
  PID_p = 0.01*kp * PID_error;
  PID_i = 0.01*PID_i + (ki * PID_error);
  
  prevTime = currTime;
  currTime = millis();
  elapsedTime = (currTime - prevTime) / 1000; 
  // PID_d = 0.01*kd*((PID_error - PID_prevError)/elapsedTime);
  PID_value = PID_p + PID_i;

  if(PID_value < 0){
    PID_value = 0;
  } else if(PID_value > 1000){
    PID_value = 1000;
  }

  PID_prevError = PID_error;

  return PID_value;
}

void loop()
{
  float currTemp;
  int heatSetting;

  setTemp = 180;
  kP = 5;
  kI = 10;
  kD = 60;
  
  currTemp = thermocouple.readCelsius();
  heatSetting = calcPID(currTemp, kP, kI, kD);

  Serial.print("temperature:");
  Serial.print(currTemp);
  Serial.print(",pwm:");
  Serial.println(heatSetting / 10.0);


  // Poor man's PWM
  if(heatSetting > 50) {
    digitalWrite(heatingElement, HIGH);
  }
  delay(heatSetting);

  if(heatSetting < 950) {
    digitalWrite(heatingElement, LOW);
  }
  delay(1000 - heatSetting);

}
