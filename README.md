# Temperature-Control-SOPDT

This repository contains Arduino and Python code I put together to do a temperature control project. The goal was to use PID control to heat a thin graphite slab to 115 F and maintain it. One of the Arduino files uses an on/off controller for the 
purposes of obtaining a graphical second order plus dead time model (SOPDT) for potential use with known PID tuning correlations, and the other uses a PID algorithm with anti-reset wind up. The Python script works with both of the Arduino 
files to plot the measured temperatures and heater power output in real time autonomously. Simply start the Arduino script first, then the Python script, and the Arduino will power the heaters and send data to Python to be plotted until the
set time has passed. Once the time is up, the Arduino sends a flag to Python to plot the final results and save the data to a CSV file. My specific setup uses a ds18b20 temperature sensor and silicone resisitive heaters powered with a MOSFET 
circuit. However, this general framework for temperature control and real time plotting should work for other simple temperature sensors and heaters. 

Here are the libraries I used for the temperature sensors:

Miles Burton's DallasTemperature.h library
https://www.milesburton.com/w/index.php/Dallas_Temperature_Control_Library

Paul Stoffregen's OneWire.h library
http://www.pjrc.com/teensy/td_libs_OneWire.html


More helpful resources:

I used Rui Santos's tutorial to work with the above libraries to obtain temperature data
https://randomnerdtutorials.com/guide-for-ds18b20-temperature-sensor-with-arduino/

APMonitor's TCLab course helped me learn about the relevant control theory and was my introduction to Python
http://apmonitor.com/heat.htm


