/*****************************************************************************
 * FILE NAME: Cellie.h                                                       *
 *                                                                           * 
 * PURPOSE: This is a header file that contains the interface for class      *
 *          Cellie. This interface defines all variables and methods to be   * 
 *          used in the class. This class is the arduino implementation of   *      
 *          the C. Elegans locomotive event-based model developed in previous*
 *          work on System Verilog.                                          * 
 *                                                                           *
 * GLOBAL VARIABLES:                                                         *
 *                                                                           *
 * Variable    Type            Description                                   *
 * --------    ----            -----------                                   *
 *  pin1       bool            Relay module pin 1                            *
 *  pin2       bool            Relay module pin 2                            *
 *  pin3       bool            Relay module pin 3                            *
 *  pin4       bool            Relay module pin 4                            *
 *  pin5       bool            Relay module pin 5                            *
 *  pin6       bool            Relay module pin 6                            *
 *  next_dm    bool array      Dorsal Muscle cell next segment               *
 *  next_vm    bool array      Ventral Muscle cell next segment              *
 *  next_db    bool array      Dorsal anterior motor neuron next segment     *
 *  next_vb    bool array      Ventral anterior motor neuron next segment    *
 *  next_da    bool array      Dorsal posterior motor neuron next segment    *
 *  next_va    bool array      Ventral posterior motor neuron next segment   *
 *  next_dd    bool array      Dorsal inhibitory neuron next segment         *
 *  next_vd    bool array      Ventral inhibitory neuron next segment        *
 *  va         bool array      Ventral posterior motor neuron                *
 *  vb         bool array      Ventral anterior motor neuron                 *
 *  vd         bool array      Ventral inhibitory neuron                     *
 *  da         bool array      Dorsal posterior motor neuron                 *
 *  db         bool array      Dorsal anterior motor neuron                  *
 *  dd         bool array      Dorsal inhibitory neuron                      *
 *  dm         bool            Dorsal Muscle cell                            *  
 *  vm         bool            Ventral Muscle cell                           *
 *  dm_fwd     bool            Dorsal Muscle cell forward segment            *
 *  vm_fwd     bool            Ventral Muscle cell forward segment           *
 *  dm_bwd     bool            Dorsal Muscle cell previous segment           *
 *  vm_bwd     bool            Ventral Muscle cell previous segment          *
 *  ava        bool            Global synchronisation region a               *
 *  avb        bool            Global synchronisation region b               *
 *                                                                           *
 * DEVELOPMENT HISTORY:                                                      * 
 *                                                                           *
 * Date      Author       Description of Change                              *
 * ----      ------       ---------------------                              *
 * 09/03/23  M. Petrou    First draft of class                               *                                                   
 * 30/04/23  M. Petrou    Final draft of class                               *
 *****************************************************************************/

#ifndef CELLIE_H
#define CELLIE_H

#include <Arduino.h>

class Cellie {
  private:
    byte pin1;     // Relay module pin right muscle
    byte pin2;     // Relay module pin left muscle
    byte pin3;     // Relay module pin right muscle
    byte pin4;     // Relay module pin left muscle
    byte pin5;     // Relay module pin right muscle
    byte pin6;     // Relay module pin left muscle

//    bool next_dm; // Dorsal Muscle cell next segment
//    bool next_vm; // Ventral Muscle cell next segment
    boolean next_db[10]; // Dorsal anterior motor neuron next segment
    boolean next_vb[10]; // Ventral anterior motor neuron next segment
    boolean next_da[10]; // Dorsal posterior motor neuron next segment
    boolean next_va[10]; // Ventral posterior motor neuron next segment
    boolean next_dd[10]; // Dorsal inhibitory neuron next segment
    boolean next_vd[10]; // Ventral inhibitory neuron next segment   

    // should these go somewhere else?
    boolean va[10];      // Ventral posterior motor neuron
    boolean vb[10];      // Ventral anterior motor neuron
    boolean vd[10];      // Ventral inhibitory neuron
    boolean da[10];      // Dorsal posterior motor neuron
    boolean db[10];      // Dorsal anterior motor neuron
    boolean dd[10];      // Dorsal inhibitory neuron
    
  public:
    boolean next_dm[10]; // Dorsal Muscle cell next segment
    boolean next_vm[10]; // Ventral Muscle cell next segment
  
    Cellie() {}                    // Class constructor - do not use this one

    // will likely use 2 pins per segment (2 valves)
    Cellie(byte pin1, byte pin2, byte pin3, byte pin4, byte pin5, byte pin6);              // Overloaded class constructor that accepts a byte argument
    
    void init();                   // initialises the built-in LED pin as an output
    void init(byte defaultState);  // overloaded to optionally set initial state of 
                                   // LED depending on the value of the defaultState argument.
    
    void on(byte pinUse);                     // turn on the LED/Relay module
    void off(byte pinUse);                    // turn off the LED/Relay module 

    void reset();                       // resets the state of cell/neuron variables of the Cellie class.
    void clockedge(bool dm, bool vm, int i);   // updates the state of the cell/neuron variables to their next values calculated by 
                                        // the previous functions and sets the state of the LED/Relay module pins based on the 
                                        // current state of the muscle cell.

    //    bool dm_fwd = Dorsal Muscle cell forward segment
    //    bool vm_fwd = Ventral Muscle cell forward segment
    //    bool dm_bwd = Dorsal Muscle cell previous segment
    //    bool vm_bwd = Ventral Muscle cell previous segment                                    
    void segment(bool dm, bool vm, bool dm_fwd, bool vm_fwd, bool dm_bwd, bool vm_bwd, bool ava, bool avb, int i);    // calculates the next state of the cell/neuron variables for all body segments.
    void head(bool dm, bool vm, bool drn, bool vrn, bool dm_bwd, bool vm_bwd, bool ava, bool avb);             // calculates the next state of the cell/neuron variables for head segment.
    void tail(bool dm, bool vm, bool dtn, bool vtn, bool dm_fwd, bool vm_fwd, bool ava, bool avb);             // calculate the next state of the cell/neuron variables for tail segment.
 };

#endif CELLIE_H
