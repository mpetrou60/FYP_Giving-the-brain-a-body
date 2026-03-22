/*****************************************************************************
 * FILE NAME: ValveControl.h                                                       *
 *                                                                           * 
 * PURPOSE: This is a header file that contains the interface for class      *
 *          Cellie. This interface defines all variables and methods to be * 
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

#ifndef VALVECONTROL_H
#define VALVECONTROL_H

#include <Arduino.h>

class ValveControl {
  private:
    byte pin1;     // Relay module pin right muscle
    byte pin2;     // Relay module pin left muscle

  public:
    ValveControl() {}                    // Class constructor - do not use this one

    // will likely use 2 pins per segment (2 valves)
    ValveControl(byte pin1, byte pin2);  // Overloaded class constructor that accepts a byte argument
    
    void init();                   // initialises the built-in LED pin as an output
    void init(byte defaultState);  // overloaded to optionally set initial state of 
                                   // LED depending on the value of the defaultState argument.
    
    void on(byte pinUse);          // turn on the LED/Relay module
    void off(byte pinUse);         // turn off the LED/Relay module 
};

#endif VALVECONTROL_H
