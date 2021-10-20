#include <SoftwareSerial.h>
//#include <Wire.h>

#define MOTOR_A1_PIN 13
#define MOTOR_B1_PIN 12
#define PWM_MOTOR_1 3

#define MOTOR_A2_PIN 8
#define MOTOR_B2_PIN 7
#define PWM_MOTOR_2 5
 
int motor1_speed, motor2_speed;            
String nom = "Arduino";
String msg;
// Initialize the integer variables
int pwm1;
int pwm2;

void setup() {
  Serial.begin(9600);
  pinMode(MOTOR_A1_PIN, OUTPUT);
  pinMode(MOTOR_B1_PIN, OUTPUT);
  pinMode(PWM_MOTOR_1, OUTPUT);
  pinMode(MOTOR_A2_PIN, OUTPUT);
  pinMode(MOTOR_B2_PIN, OUTPUT);
  pinMode(PWM_MOTOR_1, OUTPUT);
}

void loop() {
  readSerialPort();

  if (msg != "") {
    if (msg == "I"){
      readSerialPort();
      if (msg != ""){
         delay(10);
         high_speed();
      }}
    else if (msg == "O"){
      if(Serial.available() > 0) {
        pwm1 = Serial.parseInt();
        pwm2 = Serial.parseInt();
 
        Serial.print(pwm1); Serial.print(",");
        Serial.print(pwm2); Serial.print(",");

        if (pwm1 ==0 and pwm2 ==0){
          pwmStop();
        }
         else{
          updatePwm();
        }
        }
        }
    else if (msg == "T"){
      sendData();
      readSerialPort();
      if (msg != ""){
         delay(10);
         high_speed();
      }}}
    delay(500);
  }


void readSerialPort() {
  msg = "";
  if (Serial.available()) {
    delay(10);
    while (Serial.available() > 0) {
      msg += (char)Serial.read();
    }
    Serial.flush();
  }
}

void updatePwm(){
  if (pwm1 != pwm2){
    if (pwm1>pwm2){
      pwm1=400+pwm1;
      pwm2=200+pwm2;
    }
    else{
      pwm1=200+pwm1;
      pwm2=400+pwm2;
    }
  }
  else{
    pwm1=970+pwm1;
    pwm2=970+pwm2;
  }
  analogWrite(PWM_MOTOR_1,pwm1);
  analogWrite(PWM_MOTOR_2,pwm2);
  digitalWrite(MOTOR_A1_PIN, LOW);
  digitalWrite(MOTOR_A2_PIN, LOW);
  digitalWrite(MOTOR_B1_PIN, HIGH);
  digitalWrite(MOTOR_B2_PIN, HIGH); 
}

void pwmStop()
{
analogWrite(PWM_MOTOR_1, pwm1);
analogWrite(PWM_MOTOR_2, pwm2);
digitalWrite(MOTOR_A1_PIN, LOW); 
digitalWrite(MOTOR_B1_PIN, LOW);
digitalWrite(MOTOR_A2_PIN, LOW); 
digitalWrite(MOTOR_B2_PIN, LOW);
}

void forward()
{
sendData();
Serial.println("Moving Forward");
motor1_speed=400;
motor2_speed=400;
analogWrite(PWM_MOTOR_1, motor1_speed);
analogWrite(PWM_MOTOR_2, motor2_speed);
digitalWrite(MOTOR_A1_PIN, HIGH); 
digitalWrite(MOTOR_B1_PIN, LOW);
digitalWrite(MOTOR_A2_PIN, HIGH); 
digitalWrite(MOTOR_B2_PIN, LOW);
delay(3000);
stop(); 
}

void backward()
{
sendData();
Serial.println("Moving Backward");
motor1_speed=400;
motor2_speed=400;
analogWrite(PWM_MOTOR_1, motor1_speed);
analogWrite(PWM_MOTOR_2, motor2_speed);
digitalWrite(MOTOR_A1_PIN, LOW); 
digitalWrite(MOTOR_B1_PIN, HIGH);
digitalWrite(MOTOR_A2_PIN, LOW); 
digitalWrite(MOTOR_B2_PIN, HIGH);
delay(100);
stop();
}

void fforward()
{
sendData();
Serial.println("Moving Forward");
motor1_speed=1020;
motor2_speed=1020;
analogWrite(PWM_MOTOR_1, motor1_speed);
analogWrite(PWM_MOTOR_2, motor2_speed);
digitalWrite(MOTOR_A1_PIN, LOW); 
digitalWrite(MOTOR_B1_PIN, HIGH);
digitalWrite(MOTOR_A2_PIN, LOW); 
digitalWrite(MOTOR_B2_PIN, HIGH);
delay(3000);
stop(); 
}

void fbackward()
{
sendData();
Serial.println("Moving Backward");
motor1_speed=1020;
motor2_speed=1020;
analogWrite(PWM_MOTOR_1, motor1_speed);
analogWrite(PWM_MOTOR_2, motor2_speed);
digitalWrite(MOTOR_A1_PIN, HIGH); 
digitalWrite(MOTOR_B1_PIN, LOW);
digitalWrite(MOTOR_A2_PIN, HIGH); 
digitalWrite(MOTOR_B2_PIN, LOW);
delay(1500);
//motor1_speed=400;
//motor2_speed=400;
//analogWrite(PWM_MOTOR_1, motor1_speed);
//analogWrite(PWM_MOTOR_2, motor2_speed);
//digitalWrite(MOTOR_A1_PIN, LOW); 
//digitalWrite(MOTOR_B1_PIN, HIGH);
//digitalWrite(MOTOR_A2_PIN, HIGH); 
//digitalWrite(MOTOR_B2_PIN, LOW);
//delay(400);
stop();
}

void stop()
{
motor1_speed=0;
motor2_speed=0;
analogWrite(PWM_MOTOR_1, motor1_speed);
analogWrite(PWM_MOTOR_2, motor2_speed);
digitalWrite(MOTOR_A1_PIN, LOW); 
digitalWrite(MOTOR_B1_PIN, LOW);
digitalWrite(MOTOR_A2_PIN, LOW); 
digitalWrite(MOTOR_B2_PIN, LOW);
}

void ffrontright()
{
sendData();
Serial.println("Front Right");
motor1_speed=1020;
motor2_speed=200;
analogWrite(PWM_MOTOR_1, motor1_speed);
analogWrite(PWM_MOTOR_2, motor2_speed);
digitalWrite(MOTOR_A1_PIN, HIGH); 
digitalWrite(MOTOR_B1_PIN, LOW);
digitalWrite(MOTOR_A2_PIN, HIGH); 
digitalWrite(MOTOR_B2_PIN, HIGH);

}

void ffrontleft()
{
sendData();
Serial.println("Front Left");
motor1_speed=200;
motor2_speed=1020;
analogWrite(PWM_MOTOR_1, motor1_speed);
analogWrite(PWM_MOTOR_2, motor2_speed);
digitalWrite(MOTOR_A1_PIN, HIGH); 
digitalWrite(MOTOR_B1_PIN, HIGH);
digitalWrite(MOTOR_A2_PIN, HIGH); 
digitalWrite(MOTOR_B2_PIN, LOW);
}

void frontright()
{
motor1_speed=600;
motor2_speed=200;
analogWrite(PWM_MOTOR_1, motor1_speed);
analogWrite(PWM_MOTOR_2, motor2_speed);
digitalWrite(MOTOR_A1_PIN, HIGH); 
digitalWrite(MOTOR_B1_PIN, LOW);
digitalWrite(MOTOR_A2_PIN, HIGH); 
digitalWrite(MOTOR_B2_PIN, HIGH);
Serial.println("Front Right");
}

void frontleft()
{
motor1_speed=200;
motor2_speed=600;
analogWrite(PWM_MOTOR_1, motor1_speed);
analogWrite(PWM_MOTOR_2, motor2_speed);
digitalWrite(MOTOR_A1_PIN, HIGH); 
digitalWrite(MOTOR_B1_PIN, HIGH);
digitalWrite(MOTOR_A2_PIN, HIGH); 
digitalWrite(MOTOR_B2_PIN, LOW);
Serial.println("Front Left");
}

void left()
{
sendData();
Serial.println("Moving Left");
motor1_speed=400;
motor2_speed=400;
analogWrite(PWM_MOTOR_1, motor1_speed);
analogWrite(PWM_MOTOR_2, motor2_speed);
digitalWrite(MOTOR_A1_PIN, HIGH); 
digitalWrite(MOTOR_B1_PIN, LOW);
digitalWrite(MOTOR_A2_PIN, LOW); 
digitalWrite(MOTOR_B2_PIN, HIGH);
delay(500);
stop();
}


void right()
{
sendData();
Serial.println("Moving Right");
motor1_speed=400;
motor2_speed=400;
analogWrite(PWM_MOTOR_1, motor1_speed);
analogWrite(PWM_MOTOR_2, motor2_speed);
digitalWrite(MOTOR_A1_PIN, LOW); 
digitalWrite(MOTOR_B1_PIN, HIGH);
digitalWrite(MOTOR_A2_PIN, HIGH); 
digitalWrite(MOTOR_B2_PIN, LOW);
delay(500);
stop();
}

void low_speed()
{
 
  if (msg== "s" or msg=="S")
{
backward();
}
 
else if (msg== "W" or msg=="w")
{
forward();
}

else if (msg== "d" or msg=="D")
{
right();
}
 
else if (msg== "a" or msg=="A")
{
left();
}

//else if (msg== "FL" or msg=="fl")
//{
//frontleft();
//}
// 
//else if (msg== "FR" or msg=="fr")
//{
//frontright();
//}

else if(msg=="Q" or msg=="q"){
sendData();
Serial.print(" Stopping");
stop();
     }
else
{
stop();
} 
}



void high_speed()
{
if (msg== "b" or msg=="B")
{
fbackward();
}
 
else if (msg== "F" or msg=="f")
{
fforward();
}

else if (msg== "R" or msg=="r")
{
right();
}
 
else if (msg== "L" or msg=="l")
{
left();
}

//else if (msg== "FL" or msg=="fl")
//{
//ffrontleft();
//}
// 
//else if (msg== "FR" or msg=="fr")
//{
//ffrontright();
//}

else if(msg=="S" or msg=="s"){
sendData();
Serial.print(" Stopping");
stop();
     }
else
{
stop();
} 
}


void sendData() {
  //write data
  Serial.print(nom);
  Serial.print(" received : ");
  Serial.print(msg);
  Serial.print(" => ");
}
