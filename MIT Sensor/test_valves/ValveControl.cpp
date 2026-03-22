 /****************************************************************************
 * FILE NAME: ValveControl.cpp                                                     *
 *                                                                           * 
 * PURPOSE: This is a C++ file that contains the implementation for class    *
 *          Cellie. This implementation contains all the class methods     * 
 *          used in the class. This class is the arduino implementation of   *      
 *          the C. Elegans locomotive event-based model developed in previous*
 *          work on System Verilog.                                          * 
 *                                                                           *
 * GLOBAL VARIABLES:                                                         *
 *                                                                           *
 * Variable          Type      Description                                   *
 * --------          ----      -----------                                   *
 *  pin1             bool      Relay module pin                              *
 *  pin2             bool      Relay module pin                              *
 *                                                                           *
 * DEVELOPMENT HISTORY:                                                      * 
 *                                                                           *
 * Date      Author       Description of Change                              *
 * ----      ------       ---------------------                              *
 * 09/03/23  M. Petrou    First draft of class                               *                                                   *
 *****************************************************************************/

#include "ValveControl.h"  // user include file

// will likely use 2 pins per segment (2 valves)
ValveControl::ValveControl(byte pin1, byte pin2) {
  /* 
   * The Cellie constructor accepts a byte argument pin.
   * This pin is set to equal the class global variable pin.
   */
  this -> pin1 = pin1;
  this -> pin2 = pin2;
}

void ValveControl::init() {
  /* 
   * This method initialises the Cellie class by initialising the built-in 
   * LED pin as an output.
   */

   pinMode(pin1, OUTPUT);
   digitalWrite(pin1,HIGH); // Normally ON Only For Chanies Relay Module
   pinMode(pin2, OUTPUT);
   digitalWrite(pin2,HIGH); // Normally ON Only For Chanies Relay Module
}

void ValveControl::init(byte defaultState) {
  /*
   * The init method can be overloaded to optionally set initial state of the 
   * LED depending on the value of the defaultState argument.
   */
  init(); // don't have to re-write code
  if (defaultState == HIGH) {
    on(pin1);
    on(pin2);
  }
  else {
    off(pin1);
    off(pin2);
  }
}

void ValveControl::on(byte pinUse) {
  /*
   * turn on the LED/Relay module.
   */
//  digitalWrite(LED_BUILTIN, HIGH); // may have to switch to LOW for valves
  digitalWrite(pinUse, HIGH); // may have to switch to LOW for valves
}

void ValveControl::off(byte pinUse) {
  /*
   * turn off the LED/Relay module.
   */
//  digitalWrite(LED_BUILTIN, LOW); // may have to switch to HIGH for valves
  digitalWrite(pinUse, LOW); // may have to switch to HIGH for valves
}
