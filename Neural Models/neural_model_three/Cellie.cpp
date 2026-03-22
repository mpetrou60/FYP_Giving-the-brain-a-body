 /****************************************************************************
 * FILE NAME: Cellie.cpp                                                     *
 *                                                                           * 
 * PURPOSE: This is a C++ file that contains the implementation for class    *
 *          Cellie. This implementation contains all the class methods     * 
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

#include "Cellie.h"  // user include file

// will likely use 2 pins per segment (2 valves)
Cellie::Cellie(byte pin1, byte pin2, byte pin3, byte pin4, byte pin5, byte pin6) {
  /* 
   * The Cellie constructor accepts a byte argument pin.
   * This pin is set to equal the class global variable pin.
   */
  this -> pin1 = pin1;
  this -> pin2 = pin2;
}

void Cellie::init() {
  /* 
   * This method initialises the Cellie class by initialising the built-in 
   * LED pin as an output.
   */
  pinMode(LED_BUILTIN, OUTPUT);

  // Switch to this for valves
  // pinMode(pin1, OUTPUT);
  // digitalWrite(pin1,HIGH); // Normally ON Only For Chanies Relay Module
  // pinMode(pin2, OUTPUT);
  // digitalWrite(pin2,HIGH); // Normally ON Only For Chanies Relay Module
}

void Cellie::init(byte defaultState) {
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

void Cellie::on(byte pinUse) {
  /*
   * turn on the LED/Relay module.
   */
  digitalWrite(LED_BUILTIN, HIGH); // test using in-built LED for proof of concept
//  digitalWrite(pinUse, LOW); // switch to LOW for valves/pump as they are active LOW
}

void Cellie::off(byte pinUse) {
  /*
   * turn off the LED/Relay module.
   */
  digitalWrite(LED_BUILTIN, LOW); // test using in-built LED for proof of concept
//  digitalWrite(pinUse, HIGH); // switch to HIGH for valves/pump as they are active LOW
}

void Cellie::reset() 
{
  /*
   * Resets the state of cell/neuron variables of the Cellie class.
   */
  for (int i = 0; i <= 9; i++) {
      next_dm[i] = 0;
      next_vm[i] = 0;

      next_db[i] = 0;
      next_vb[i] = 0;
      
      next_da[i] = 0;
      next_va[i] = 0;

      next_dd[i] = 0;
      next_vd[i] = 0;   
  }
}

 void Cellie::segment(bool dm, bool vm, bool dm_fwd, bool vm_fwd, bool dm_bwd, bool vm_bwd, bool ava, bool avb, int i) 
 {
  /*
   * Calculates the next state of the cell/neuron variables for all body segments.
   */
  next_dm[i] = ((da[i] || db[i]) && !dd[i]) || (dm && !dd[i]);
  next_vm[i] = ((va[i] || vb[i]) && !vd[i]) || (vm && !vd[i]);

  next_db[i] = avb && dm_fwd;
  next_vb[i] = avb && vm_fwd;

  next_da[i] = ava && dm_bwd;
  next_va[i] = ava && vm_bwd;

  next_dd[i] = va[i] || vb[i];
  next_vd[i] = da[i] || db[i];   
  }

 void Cellie::head(bool dm, bool vm, bool drn, bool vrn, bool dm_bwd, bool vm_bwd, bool ava, bool avb) 
 {
  /*
   * Calculates the next state of the cell/neuron variables for head segment.
   */
  next_dm[0] = ((da[0] || db[0]) && !dd[0]) || ((dm || drn) && !dd[0]);
  next_vm[0] = ((va[0] || vb[0]) && !vd[0]) || ((vm || vrn) && !vd[0]);

  next_db[0] = avb;
  next_vb[0] = avb;

  next_da[0] = ava && dm_bwd;
  next_va[0] = ava && vm_bwd;

  next_dd[0] = va[0] || vrn;
  next_vd[0] = da[0] || drn;      
  }

 void Cellie::tail(bool dm, bool vm, bool dtn, bool vtn, bool dm_fwd, bool vm_fwd, bool ava, bool avb) 
 {
  /*
   * Calculates the next state of the cell/neuron variables for tail segment.
   */
  next_dm[9] = ((da[9] || db[9]) && !dd[9]) || ((dm || dtn) && !dd[9]);
  next_vm[9] = ((va[9] || vb[9]) && !vd[9]) || ((vm || vtn) && !vd[9]);

  next_db[9] = avb && dm_fwd;
  next_vb[9] = avb && vm_fwd;

  next_da[9] = ava;
  next_va[9] = ava;

  next_dd[9] = vb[9] || vtn;
  next_vd[9] = db[9] || dtn;   
  }   

void Cellie::clockedge(bool dm, bool vm, int i) 
{
  /*
   * updates the state of the cell/neuron variables to their next values calculated by 
   * the previous functions and sets the state of the LED/Relay module pins based on the 
   * current state of the muscle cell.
   * i defines the segment being updated. Segment 2 is the one being controlled.
   */
  dm = next_dm[i];
  if  ((dm == true) && (i == 0)) {
     on(pin1); // turn the LED on (HIGH is the voltage level) 
  }
  else {
     off(pin1); // turn the LED off (LOW is the voltage level)
  }

  if  ((dm == true) && (i ==1)) {
     on(pin3); // turn the LED on (HIGH is the voltage level) 
  }
  else {
     off(pin3); // turn the LED off (LOW is the voltage level)
  }

  if  ((dm == true) && (i == 2)) {
     on(pin5); // turn the LED on (HIGH is the voltage level) 
  }
  else {
     off(pin5); // turn the LED off (LOW is the voltage level)
  }
  
  vm = next_vm[i];
  if  ((vm == true) && (i == 0)) {
     on(pin2); // turn the LED on (HIGH is the voltage level) 
  }
  else {
     off(pin2); // turn the LED off (LOW is the voltage level)
  }

  if  ((vm == true) && (i == 1)) {
     on(pin4); // turn the LED on (HIGH is the voltage level) 
  }
  else {
     off(pin4); // turn the LED off (LOW is the voltage level)
  }

  if  ((vm == true) && (i == 2)) {
     on(pin6); // turn the LED on (HIGH is the voltage level) 
  }
  else {
     off(pin6); // turn the LED off (LOW is the voltage level)
  }
  
  db[i] = next_db[i];
  vb[i] = next_vb[i];
  
  da[i] = next_da[i];
  va[i] = next_va[i];
  
  dd[i] = next_dd[i];
  vd[i] = next_vd[i];
  }
