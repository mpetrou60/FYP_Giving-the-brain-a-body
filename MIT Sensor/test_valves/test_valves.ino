/*****************************************************************************
 * FILE NAME: test_model                                                     *
 *                                                                           * 
 * PURPOSE: This is a test file for controlling the device. The device       *  
 *          will follow the locomotive behaviour of the C. Elegans which has *
 *          been defined in a class in the Cellie.h file. This class is the  *
 *          arduino implementation of the C. Elegans locomotive event-based  *
 *          model developed in previous work on System Verilog.              * 
 *                                                                           *
 * FILE REFERENCES:                                                          *
 *                                                                           *
 * Name                Description                                           *
 * ----                -----------                                           *
 * ValveControl.h      Header file that contains the interface for class.    *
 *                     Interface defines all variables/ methods.             *
 * ValveControl.cpp    C++ file that contains the implementation for class.  *
 *                     Implementation contains all class methods.            *
 *                                                                           *
 * EXTERNAL VARIABLES:                                                       *
 * Source: <ValveControl.h>                                                  *
 *                                                                           *
 * Variable          Type      Description                                   *
 * --------          ----      -----------                                   *
 *  pin1             bool      Relay module pin                              *
 *  pin2             bool      Relay module pin                              *                       *
 *                                                                           *
 * ABNORMAL TERMINATION CONDITIONS, ERROR AND WARNING MESSAGES:              *
 *                                                                           *
 * ASSUMPTIONS, CONSTRAINTS, RESTRICTIONS:                                   *
 *                                                                           *
 * NOTES:                                                                    *
 *                                                                           *
 * REQUIREMENTS/FUNCTIONAL SPECIFICATIONS REFERENCES:                        *
 *                                                                           *
 * DEVELOPMENT HISTORY:                                                      * 
 *                                                                           *
 * Date      Author       Description of Change                              *
 * ----      ------       ---------------------                              *
 * 21/03/23  M. Petrou    First draft of class                               *                                                   *
 *****************************************************************************/

// *** VALVES ****************************************************************
// (LED = placeholder)
#define valve1Pin 12
#define valve2Pin 13
#define randomPin 8

// *** PUMP ******************************************************************
#define pump1Pin A3 // check pin
#define pump2Pin A5 // check pin

// *** CLOCK *****************************************************************
unsigned long delayStart = 0; // the time the delay started
int i = 0;
int count = 0;

// Call header file containing neural network class
#include "ValveControl.h"

// Define neural network instance for main script
ValveControl valve(pump1Pin, pump2Pin);

void setup() {
  Serial.begin(9600);
  Serial.println("Valve Tests");
  
  valve.init(HIGH);         // initialises the built-in LED pin as an output.

  pinMode(randomPin, OUTPUT);
  digitalWrite(randomPin, HIGH); 

  // Switch pump on 
  // pinMode(pump1Pin, OUTPUT);
  // digitalWrite(pump1Pin, HIGH); 
  // pinMode(pump2Pin, OUTPUT);
  // digitalWrite(pump2Pin, HIGH); 
}

void loop() {
  // code for one segment
  if (i == 0) {
    valve.off(pump1Pin);
    valve.off(pump2Pin);
    Serial.println("2000 delay: 1 & 2 on"); // on is off...
    delay(2000);
     
    valve.on(pump1Pin);
    valve.on(pump2Pin);
    Serial.println("1 & 2 off");
    delay(2000);
    if (count < 10) {
      count = count + 1;
    }
    else {
      count = 0;
      delay(4000);
      i = i + 1;
    }
  }

  
  if (i == 1) {
    valve.off(pump1Pin);
    valve.off(pump2Pin);
    Serial.println("500 delay:1 & 2 on"); // on is off...
    delay(500);
     
    valve.on(pump1Pin);
    valve.on(pump2Pin);
    Serial.println("1 & 2 off");
    delay(500);
    if (count < 40) {
      count = count + 1;
    }
    else {
      count = 0;
      delay(4000);
      i = i + 1;
    }
  }

  if (i == 2) {
    valve.off(pump1Pin);
    valve.off(pump2Pin);
    Serial.println("1000 delay:1 & 2 on"); // on is off...
    delay(1000);
     
    valve.on(pump1Pin);
    valve.on(pump2Pin);
    Serial.println("1 & 2 off");
    delay(1000);
    if (count < 20) {
      count = count + 1;
    }
    else {
      count = 0;
      delay(4000);
      i = 0;
    }
  }
}
