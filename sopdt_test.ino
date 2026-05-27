
//From Paul Stoffregen

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
double Q;
double t= 0.0;
double flag = 998.0;
double check;
double t_total = 610.0;
double sp;
double sp_end = 115.0;



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
delay(20000);
}

void loop(void){ 
// Call sensors.requestTemperatures() to issue a global temperature and Requests to all devices on the bus
if (t < t_total) {
loop_start = millis();
sensors.requestTemperatures(); 

T = sensors.getTempFByIndex(0);


if (t<10) {
analogWrite(6,0);
Q = 0.0;
}

// On/off kicks in
if (t>=10) {

  
  //on
  if (T<sp_end) {
  analogWrite(6,255);
  Q = 100.0;
  }
  //off
  if (T>= sp_end) {
    analogWrite(6,0);
    Q = 0.0;
  }


}


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
}
if (t >= t_total) {
  flag = 999.0;
  Serial.print(flag);
Serial.print(',');
Serial.print(t);
Serial.print(',');
Serial.print(T);
Serial.print(',');
Serial.println(Q);
}
}

