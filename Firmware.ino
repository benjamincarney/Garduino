// Include Libraries
#include "Arduino.h"
#include "Wire.h"
#include "RTClib.h"
#include "SoilMoisture.h"
#include "SolenoidValve.h"


// Pin Definiti
#define SOILMOISTURE_PIN_SIG	A3
#define SOLENOIDVALVE_PIN_COIL1	2



// Global variables and defines

// object initialization
RTC_DS3231 rtc;
SoilMoisture soilMoisture(SOILMOISTURE_PIN_SIG);
SolenoidValve solenoidValve(SOLENOIDVALVE_PIN_COIL1);



// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    if (! rtc.begin()) {
        Serial.println("Couldn't find RTC");
        while (1);
      }

      if (rtc.lostPower()) {
        Serial.println("RTC lost power, lets set the time!");
        // following line sets the RTC to the date & time this sketch was compiled
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
        // This line sets the RTC with an explicit date & time, for example to set
        // January 21, 2014 at 3am you would call:
        // rtcadjust(DateTime(2014, 1, 21, 3, 0, 0));
      }
    menuOption = menu();
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    
    
    if(menuOption == '1') {
    // DS3231 Precision RTC Breakout - Test Code
    //This will display the time and date of the RTC. see RTC.h for more functions such as rtc.hour(), rtc.month() etc.
    DateTime now = rtc.now();
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print('/');
    Serial.print(now.year(), DEC);
    Serial.print("  ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    delay(1000);
    }
    else if(menuOption == '2') {
    // Soil Moisture Sensor - Test Code
    int soilMoistureVal = soilMoisture.read();
    Serial.print(F("Val: ")); Serial.println(soilMoistureVal);

    }
    else if(menuOption == '3') {
    // 12V Solenoid Valve - 3/4'' - Test Code
    // The solenoid valve will turn on and off for 500ms (0.5 sec)
    solenoidValve.on(); // 1. turns on
    delay(500);       // 2. waits 500 milliseconds (0.5 sec). Change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    solenoidValve.off();// 3. turns off
    delay(500);       // 4. waits 500 milliseconds (0.5 sec). Change the value in the brackets (500) for a longer or shorter delay in milliseconds.

    }
    
    
    
    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }
    
}



// Menu function for selecting the components to be tested
// Follow serial monitor for instrcutions
char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) DS3231 Precision RTC Breakout"));
    Serial.println(F("(2) Soil Moisture Sensor"));
    Serial.println(F("(3) 12V Solenoid Valve - 3/4''"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {
            if(c == '1') 
    			Serial.println(F("Now Testing DS3231 Precision RTC Breakout"));
    		else if(c == '2') 
    			Serial.println(F("Now Testing Soil Moisture Sensor"));
    		else if(c == '3') 
    			Serial.println(F("Now Testing 12V Solenoid Valve - 3/4''"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
            }
        }
    }
