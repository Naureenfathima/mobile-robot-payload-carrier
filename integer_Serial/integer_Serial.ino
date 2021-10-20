#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

#define MOTOR_A1_PIN 13
#define MOTOR_B1_PIN 12
#define PWM_MOTOR_1 3

#define MOTOR_A2_PIN 8
#define MOTOR_B2_PIN 7
#define PWM_MOTOR_2 5

// Initialize the integer variables
int pwm1;
int pwm2;
const int rs = 2, en = 4, d4 = 6, d5 = 9, d6 = 10, d7 = 11;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
 
void setup(){
   
  // Set the baud rate  
  Serial.begin(9600);
  pinMode(MOTOR_A1_PIN, OUTPUT);
  pinMode(MOTOR_B1_PIN, OUTPUT);
  pinMode(PWM_MOTOR_1, OUTPUT);
  pinMode(MOTOR_A2_PIN, OUTPUT);
  pinMode(MOTOR_B2_PIN, OUTPUT);
  pinMode(PWM_MOTOR_1, OUTPUT); 
  lcd.begin(16, 2);
}
 
void loop(){
  lcd.clear();
  
  if(Serial.available() > 0) {
    lcd.print("Follow Me");
    pwm1 = Serial.parseInt();
    pwm2 = Serial.parseInt();
 
    // We do println to add a new line character '\n' at the end
    // of the comma-separated stream of integers
    Serial.print(pwm1); Serial.print(",");
    Serial.print(pwm2); Serial.print(",");

    if (pwm1 ==0 and pwm2 ==0){
      pwmStop();
    }
    else{
      updatePwm();
    }
    }
    lcd.clear();
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
