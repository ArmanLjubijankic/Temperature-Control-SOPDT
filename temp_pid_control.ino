
// From Paul Stoffergen
#include <OneWire.h>

//MIT License
//Copyright (c) 2024 Miles Burton
//Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include <DallasTemperature.h>



// Data wire is connected to the Arduino digital pin 4
#define ONE_WIRE_BUS 4
double loop_start;
double T;
double T_old;
double Q;
double t= 0.0;
double flag = 998.0;
double check;
double t_total = 610.0;
double sp;
double sp_end = 115.0;
double I = 0;
double dt = 1.0;
double error = 0.0;
double op;
double a = 0;
double alpha = .5;
// approximate SOPDT model from
//Steady state temperature of about 116 F
//A maximum temperature of about 122 F with peak time 126 s
//Starting temperature of about 70 F
//Set point at 115 F
//Dead time of 6 s
double kp = (46.0/45.0);
double zeta = .545;
double D = 6.0;
double tau_s = 32.6;

//PID parameters, IMC-Chien as baseline
double lambda = max(.25*D,.2*tau_s);
double kc = .0087*(2*zeta*tau_s)/(kp*(lambda+D));
double td = tau_s/(2*zeta);
double ti = 2*zeta*tau_s;
double kd = kc*td/5.0;
double ki = 2.0*.01*30.0*kc/ti;



// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

void setup(void)
{
// Start serial communication for debugging purposes
Serial.begin(9600);
// Start up the library
sensors.begin();
pinMode(6, OUTPUT);
delay(10000);
}

void loop(void){ 
// Call sensors.requestTemperatures() to issue a global temperature and Requests to all devices on the bus
if (t < t_total) {
loop_start = millis();
sensors.requestTemperatures(); 

T = sensors.getTempFByIndex(0);

//setpoints
if (t<10) {
sp =68.0;
}

if (t>=10) {
  sp = 115.0;
}

//PID control

error = sp - T;
I = I + (double)(ki)*error*dt;
op = (double)kc*error - (double)kd*(T-T_old)/dt + I;

// Anti-reset wind up
if (op < 0.0 || op > 255.0) {
  I = I - ki*error*dt;
  op = max(0,min(255.0,op));
}

digitalWrite(6,op);
Q = (double)(op/255.0)*100.0;

// Commented lines below can be used to quickly isolate results on the Arduino end


//Serial.println(I);
//Serial.println(kc);
//Serial.println(kd);
//Serial.println(ki);
//Serial.println(op);
//Serial.println(T);
//T_old = T;
//t = t + 1;
//if (a == 1) {

Serial.print(flag);
Serial.print(',');
Serial.print(t);
Serial.print(',');
Serial.print(T);
Serial.print(',');
Serial.print(Q);
if (t < 1) {
  Serial.print(',');
  Serial.print(sp_end);
  Serial.print(',');
  Serial.println(t_total);
}
if (t >=1) {
  Serial.print('\n');
}

t = t + 1;
double check = millis()- loop_start;
while (check < 1000) {
check = millis()- loop_start;
}
T_old = T;
//}
if (t >= t_total) {
  flag = 999.0;
  Serial.print(flag);
Serial.print(',');
Serial.print(t);
Serial.print(',');
Serial.print(T);
Serial.print(',');
Serial.println(Q);
digitalWrite(6,0);
}
}
}

