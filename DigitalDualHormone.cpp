#include <TimerOne.h>
int M1_PWM=5;
int M2_PWM=6;
const float min_ph=7.3;
const float max_ph=9.3;
const float target_ph=7.5;//upper threshold
const float min_phgluc=3;
const float max_phgluc=7.25; //lower threshold, establishing target
zone
const float target_phgluc=7.25;
int M1_D1=4;
int M1_D0=3;
int M2_D1=7;
int M2_D0=8;
const int ph_sensor_pin=0;
float PWMMOTORvalue;
float ph_value;
float glucagonpump;
float insulinpump;
float voltage;
void setup () {
pinMode(M1_PWM, OUTPUT);
pinMode(M1_D1, OUTPUT);
pinMode(M1_D0, OUTPUT);

pinMode(M2_PWM, OUTPUT);
pinMode(M2_D1, OUTPUT);
pinMode(M2_D0, OUTPUT);

87

digitalWrite(M1_D0, 0);
digitalWrite(M1_D1, 1);

digitalWrite(M2_D0, 1);
digitalWrite(M2_D1, 0);
Serial.begin(9600);
Timer1.initialize(1000000/5);
Timer1.attachInterrupt(callback);
}

void callback () {
voltage=analogRead(ph_sensor_pin)*5.0/1024;//scaling the pH value
accroding to the voltage
ph_value=voltage*3.5;//finding the pH value
Serial.println(ph_value);
//analogWrite(M2_PWM, 200)
if (ph_value>=target_ph)// if the solution is basic, the following
steps will be followed, this part is identical to the single hormone’s
system, the insulin pump’s logic
{

PWMMOTORvalue=150+(ph_value-target_ph)*(255-150)/(max_ph-
min_ph);//if the solution is extremely basic the motor's speed will

increase
analogWrite(M1_PWM, PWMMOTORvalue);//if the solution's pH becomes
closer to the value of the target pH the motor's speed will decrease,
prevents the motor overshooting
Serial.println("insulin"); //inform what pump is on
Serial.println(PWMMOTORvalue);//print PWM value, for
troubleshooting
}
else if(ph_value<=target_phgluc) //if the pH value is less than the
lower threshold

88

{

PWMMOTORvalue=150+(target_phgluc-ph_value)*(255-150)/(max_phgluc-
min_phgluc);//scaling the glucagon pump

analogWrite(M2_PWM, PWMMOTORvalue); //the PWM value, or the speed
of the glucagon pump will depend on the pH of the solution
Serial.println ("glucagon"); //inform what pump is running
Serial.println (PWMMOTORvalue); //troubleshooting

}
else //if the pH is not below or above the target zone, the pH is
inside the target zone
{

analogWrite(M2_PWM, 0); //the glucagon pump is shut off
analogWrite(M1_PWM,0); //the insulin pump is shut off
Serial.println("neutral"); //included so the timer can stop when
this message appears, the pH of the solution is within the target zone
Serial.println(PWMMOTORvalue); //should appear as less than 150,
meaning the motors are switched off,

}
void loop()
}
