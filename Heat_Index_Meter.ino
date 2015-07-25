//Using an Arduino R3 a DHT22, a 16x2 LCD screen to read the sensor results and calculate the Heat Index
//Author: Daniel R.
//Version: 1.0.1
//Date: 2015-07-25


#include <LiquidCrystal.h>  // Arduino's standard library
#include <DHT.h>            // ADAfruit Library

#define DHTTYPE DHT22   // Tells the Arduino if you have the DHT11 or the DHT22
#define DHTPIN (9)      // Tells the Arduino to look for the info on Digital 9
DHT dht(DHTPIN, DHTTYPE);

const int lcdRS = 3;
const int lcdEnable = 4;
const int lcdD4 = 5;
const int lcdD5 = 6;
const int lcdD6 = 7;
const int lcdD7 = 8;

// initialize the LCD library with the numbers of the interface pins as defined above
LiquidCrystal lcd(lcdRS, lcdEnable, lcdD4, lcdD5, lcdD6, lcdD7);


// Heat Index Function
// http://en.wikipedia.org/wiki/Heat_index
double heatIndex(double Temperature, double Humidity)
{
  double c1 = -42.38, c2 = 2.049, c3 = 10.14, c4 = -0.2248, c5= -6.838e-3, c6=-5.482e-2, c7=1.228e-3, c8=8.528e-4, c9=-1.99e-6 ; 
  double T = Temperature;// The temperature reading
  double R = Humidity;// The humidity reading
  double T2 = T*T;
  double R2 = R*R;
  double TR = T*R;
  double rv = c1 + c2*T + c3*R + c4*T*R + c5*T2 + c6*R2 + c7*T*TR + c8*TR*R + c9*T2*R2;
  return rv;
}
void setup() {
//initialize lcd
   lcd.begin(16, 2);
   
   Serial.begin(9600);
  dht.begin();      //begin communication with the sensor
  
 //This is all just for show... makes it all seem legit. 
   lcd.setCursor(0,0);
   lcd.print("STARTING!");
      delay(750);
   lcd.print(".");
      delay(750);
   lcd.print(".");
      delay(750);
   lcd.print(".");
      delay(750);
   lcd.print(".");
      delay(750);
   lcd.print(".");
      delay(750);
   lcd.print(".");
      delay(750);
   lcd.print(".");
      delay(750);
   lcd.print(".");
   lcd.clear();
   lcd.print ("GETTING DATA...");
   Serial.println( "Temp,RH,HI");
      delay(5000);
   lcd.clear();
}

void loop() {  
    float Humidity =    (dht.readHumidity()); //Read the DHT humidity sensor
    float Temperature = (dht.readTemperature()* 9.0 / 5.0 + 32.0); //Read the DHT Temp, convert C to F 
    float HI =          (heatIndex(Temperature, Humidity));
//NOAA says that air temps outside of 80*F and a RH of 40%
//The if statement is to  reflect that.
  if (Temperature > 80 and Humidity > 40)
  {
    lcd.setCursor(0,0);
    lcd.print("HI: ");
    lcd.print(HI);
    lcd.print("F");
    lcd.setCursor(0,1);
    lcd.print(Temperature);
    lcd.print(" F ");
    lcd.print(Humidity);
    lcd.print("%");
    Serial.print(Temperature);
    Serial.print(",");
    Serial.print(Humidity);
    Serial.print(",");
    Serial.println(HI);
    lcd.clear();
  } 
  else
  { 
    lcd.setCursor(0,0);
    lcd.print("INDEX NOMINAL");
    lcd.setCursor(0,1);
    lcd.print(Temperature);
    lcd.print(" F ");
    lcd.print(Humidity);
    lcd.print("%");
    Serial.print(Temperature);
    Serial.print(",");
    Serial.print(Humidity);
    Serial.print(",");
    Serial.println(Temperature);
    lcd.clear();
  } 

    delay(10000);//slow it down for reading and not having a million data points
    
}

