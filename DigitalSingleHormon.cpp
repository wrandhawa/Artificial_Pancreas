#include <TimerOne.h>
int M1_PWM=5; //define pin on Arduino board
const float min_ph=7.3; //constants will remain constant throughout
experimentation
const float max_ph=9.9;
const float target_ph=7.5;
int M1_D1=4; //establishing the direction of the motor
int M1_D0=3;
const int ph_sensor_pin=0;
float PWMMOTORvalue; //speed of insulin pump

This picture shows the
digital pH sensor inside
of the baking soda
solution. The digital pH
sends the pH of the
solution to Arduino.
Throughout
experimentation, the
digital pH sensor was
extremely accurate.

84

float ph_value;
float voltage;
void setup () { //initialize pin modes, inputs and outputs
pinMode(M1_PWM, OUTPUT);
pinMode(M1_D1, OUTPUT);
pinMode(M1_D0, OUTPUT);
digitalWrite(M1_D0, 0);
digitalWrite(M1_D1, 1);
Serial.begin(9600);
Timer1.initialize(1000000/5);
Timer1.attachInterrupt(callback);
}

void callback () {
voltage=analogRead(ph_sensor_pin)*5.0/1024;//scaling the pH value
accroding to the voltage
ph_value=voltage*3.5;//finding the pH value
Serial.println(ph_value); // for troubleshooting
if (ph_value>=target_ph)// if the solution is basic
{

PWMMOTORvalue=150+(ph_value-target_ph)*(255-150)/(max_ph-
min_ph);//if the solution is extremely basic the motor's speed will

increase
analogWrite(M1_PWM, PWMMOTORvalue);//if the solution's pH becomes
closer to the value of the target pH the motor's speed will decrease
Serial.println(PWMMOTORvalue);//print PWM value, for
troubleshooting (above 150, which is the minimum threshold that the
motors runs, below 255, which is the max value for PWM)
}
else // if the solution is not acidic Arduino will skip the
directions above
{

85
analogWrite(M1_PWM, 0);// when the pH of the solution reaches the
target pH, the motor will shut off
}
}
void loop() {
}
