# HI_Meter
Wrote this to create a heat index meter to see what the temperature and Heat Index are at work.

The circuit design is fairly simple as most of the parts can be sourced from the kits that are usually included
with Arduino boards. The only piece that I bought seperately was the DHT22 from SparkFun.

# To Do:
Fritzing schematics to be completed and updated.
Add dewpoint calculation.
add formula to average out two readings to minimize instant fluctuations in readings.

#ChangeLog
- added if-statement for humidity calculations. NOAA says that erronious readings occure below 80F and 40% Relative Humidity.
- added schematics and Fritzing file.
- first commit of arduino file.



Coded for the Arduino IDE 1.6.4
