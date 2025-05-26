// C++ code
//
#include <Servo.h>

int Start_Sensor = 0;
int End_Sensor = 0;

bool first_pass = false;
unsigned long first_pass_time = 0.0000000;
unsigned long time_to_complete = 0.000000000;
unsigned long final_velocity = 0.000000000;
unsigned long acceleration = 0.000000000;
unsigned long end_pass = 0.000000000;

double servo_speed = 10;
int firstsensor_detection_value = 220;
int secondsensor_detection_value = 80;

int up_button = 10;
int down_button = 11;

int sensor_start = A1;
int sensor_end = A2;

Servo servo_main;

void setup() 
{
  // sensor
  pinMode(sensor_start, INPUT);
  pinMode(sensor_end, INPUT);
  
  // button
  pinMode(up_button, INPUT_PULLUP);
  pinMode(down_button, INPUT_PULLUP);
  
  //servo
  servo_main.attach(3, 500, 2500);
  
  Serial.begin(9600);
}

void loop()
{
  Start_Sensor = analogRead(sensor_start);
  End_Sensor = analogRead(sensor_end);

//  Serial.print("Start_Sensor: ");
//  Serial.print(Start_Sensor);
//  Serial.print(", ");
//  Serial.print("End_Sensor: ");
//  Serial.print(End_Sensor);
//  Serial.println(", ");
  
 
  if (Start_Sensor > firstsensor_detection_value && !first_pass) {
    Serial.println(' ');
//    Serial.print("Start_Sensor: "); 
//    Serial.print(Start_Sensor);
//    Serial.print(", ");
        
    first_pass = true;
    first_pass_time = millis();
//    Serial.print("first_pass_time: ");
//    Serial.println(first_pass_time);
  }
  
  
  if (first_pass && End_Sensor > secondsensor_detection_value) {
//    Serial.println(' ');
//    Serial.print("End_Sensor: ");
//    Serial.print(End_Sensor);
//    Serial.println(", ");
    
    first_pass = false;
    end_pass = millis();
    time_to_complete = end_pass - first_pass_time;
    //distance: 7.55
    final_velocity = (15.1L / time_to_complete);
    acceleration = (final_velocity / time_to_complete);

    Serial.print("Time to complete: ");
    Serial.println(time_to_complete);
//    Serial.print("final_velocity: ");
//    Serial.println(final_velocity);
//    Serial.print("millis: ");
//    Serial.println(millis());
//    Serial.print("Acceleration: ");
//    Serial.print(acceleration);
    Serial.println(" ");
  }
    
  if (digitalRead(up_button) == LOW) {
    servo_main.write(90 + servo_speed);
    delay(30);
  }
  
  else if (digitalRead(down_button) == LOW) {
    servo_main.write(90 - servo_speed);
    delay(30);
  }

  else{
    servo_main.write(90);  
  }


//  Serial.println(servo_pos);
}
