/*****************************************************************************
 * FILE NAME: neural_model_simple                                            *
 *                                                                           * 
 * PURPOSE: This is the main file for controlling the device. The device     *  
 *          will follow the locomotive behaviour of the C. Elegans which has *
 *          been defined in a class in the Cellie.h file. This class is the  *
 *          arduino implementation of the C. Elegans locomotive event-based  *
 *          model developed in previous work on System Verilog. This file is *            
 *          a simplified testbench compared to the one developed in previous *
 *          work, and limiting the design to just three segments.            * 
 *                                                                           *
 * FILE REFERENCES:                                                          *
 *                                                                           *
 * Name          Description                                                 *
 * ----          -----------                                                 *
 * Cellie.h      Header file that contains the interface for class Cellie.   *
 *               Interface defines all variables and methods used in class.  *
 * Cellie.cpp    C++ file that contains the implementation for class Cellie. *
 *               Implementation contains all class methods used in class.    *
 *                                                                           *
 * GLOBAL VARIABLES:                                                         *
 *                                                                           *
 * Variable    Type            Description                                   *
 * --------    ----            -----------                                   *
 *  pump1Pin   pin             Relay module pin connected to vacuum pump 1   *
 *  pump2Pin   pin             Relay module pin connected to vacuum pump 2   *
 *  pump3Pin   pin             Relay module pin connected to vacuum pump 3   *
 *  pump4Pin   pin             Relay module pin connected to vacuum pump 4   *
 *  pump5Pin   pin             Relay module pin connected to vacuum pump 5   *
 *  pump6Pin   pin             Relay module pin connected to vacuum pump 6   *
 *  drn        bool            Dorsal nerve ring neuron                      *
 *  dtn        bool            Dorsal tail stimulation neuron                *
 *  vrn        bool            Ventral nerve ring neuron                     *
 *  vtn        bool            Ventral tail stimulation neuron               *
 *  ava        bool            Global synchronisation region a               *
 *  avb        bool            Global synchronisation region b               *
 *  dm         bool array      Dorsal Muscle cell                            *  
 *  vm         bool array      Ventral Muscle cell                           *
 *  noSegments int             Number of segments to make up worm            *
 *  motion     int             Type of locomotion to activate                *
 *  n          int             Oscillation of neurons controller             *
 *                                                                           *
 * EXTERNAL VARIABLES:                                                       *
 * Source: <Cellie.h>                                                        *
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
 * 09/03/23  M. Petrou    First draft of class                               *                                                   
 * 30/04/23  M. Petrou    Final draft of class                               *
 *****************************************************************************/

// *** PUMP ******************************************************************
#define pump1Pin A1 // check pin
#define pump2Pin A2 // check pin
#define pump3Pin A3 // check pin
#define pump4Pin A4 // check pin
#define pump5Pin A5 // check pin
#define pump6Pin A6 // check pin

// *** HEAD AND TAIL SIGNALS **************************************************
bool drn = false;
bool vrn = false;
bool dtn = false;
bool vtn = false;

// *** GLOBAL SIGNALS *********************************************************
bool ava = false; // Global synchronisation region a
bool avb = false; // Global synchronisation region b

// *** INTERCONNECT ***********************************************************
// dm = Dorsal muscle cell, vm = Ventral Muscle cell
// these are the ones you care about for muscle activation 
   
boolean dm[10] = {false, false, false, false, false, false, false, false, false, false};
boolean vm[10] = {false, false, false, false, false, false, false, false, false, false};

// *** SETTING UP THE NEURAL MODEL *********************************************
// for multiple segments
int noSegments = 2; // 10 segments, because subscript 0 (0-9)
int i = 0;
int n = 0;
int motion = 0;  

// Call header file containing neural network class
#include "Cellie.h"

// Define neural network instance for main script
Cellie cellie(pump1Pin, pump2Pin, pump3Pin, pump4Pin, pump5Pin, pump6Pin);

void setup() {
  Serial.begin(9600);
  Serial.println("Testbench Tests");
  
  cellie.init();                // initialises the built-in LED pin as an output.
  cellie.reset();               // resets the state of cell/neuron variables of the Cellie class.
  cellie.clockedge(0, 0, 0);    // sets state of all cell/neuron variables to those that have been resetted

  for (int j = 0; j <= noSegments; j++) {
      cellie.clockedge(dm[j], vm[j], j);
      }

  // Label for data collection
  Serial.print("motion");
  Serial.print(",");
  Serial.print("ava");
  Serial.print(",");
  Serial.print("avb");
  Serial.print(",");
  Serial.print("drn");
  Serial.print(",");
  Serial.print("dtn");
  Serial.print(",");
  Serial.print("vrn");
  Serial.print(",");
  Serial.print("vtn");
  Serial.print(",");
  Serial.print("DM");
  Serial.print(",");
  Serial.println("VM");
}

void loop() {
  if (motion >= 31) {
      motion == 0;
    }
    
  // forwards motion 
  if (motion <= 5) {
    Serial.print("forwards");
    Serial.print(",");
    if (n == 0) {
      // Invert vrn and drn
      vrn = !vrn;
      drn = !vrn;
    }
  
    // invert avb
    if (n%3 == 0) { 
      avb = !avb;
    }

    // keep rest low
    dtn = false;
    vtn = false;
    ava = false;
    }

  // backwards motion 
  else if (motion <= 10) {
    Serial.print("backwards");
    Serial.print(",");
    if (n == 0) {
      // Invert vrn and drn
      vtn = !vtn;
      dtn = !vtn;
    }
  
    // invert avb
    if (n%3 == 0) { 
      ava = !ava;
    }

    // keep rest low
    avb = false;
    drn = false;
    vrn = false;
    }   

    // forwards motion 
  else if (motion <= 15) {
    Serial.print("forwards");
    Serial.print(",");
    if (n == 0) {
      // Invert vrn and drn
      vrn = !vrn;
      drn = !vrn;
    }
  
    // invert avb
    if (n%3 == 0) { 
      avb = !avb;
    }

    // keep rest low
    dtn = false;
    vtn = false;
    ava = false;
    }

  // backwards motion 
  else if (motion <= 20) {
    Serial.print("backwards");
    Serial.print(",");
    if (n == 0) {
      // Invert vrn and drn
      vtn = !vtn;
      dtn = !vtn;
    }
  
    // invert avb
    if (n%3 == 0) { 
      ava = !ava;
    }

    // keep rest low
    avb = false;
    drn = false;
    vrn = false;
    }  

    // forwards motion 
  if (motion <= 25) {
    Serial.print("forwards");
    Serial.print(",");
    if (n == 0) {
      // Invert vrn and drn
      vrn = !vrn;
      drn = !vrn;
    }
  
    // invert avb
    if (n%3 == 0) { 
      avb = !avb;
    }

    // keep rest low
    dtn = false;
    vtn = false;
    ava = false;
    }

  // backwards motion 
  else if (motion <= 30) {
    Serial.print("backwards");
    Serial.print(",");
    if (n == 0) {
      // Invert vrn and drn
      vtn = !vtn;
      dtn = !vtn;
    }
  
    // invert avb
    if (n%3 == 0) { 
      ava = !ava;
    }

    // keep rest low
    avb = false;
    drn = false;
    vrn = false;
    }      

    // coiling motion 
  else {
    Serial.print("coiling");
    Serial.print(",");
    if (n == 0) {
      // Invert vrn and drn
      vtn = !vtn;
      vrn = vtn;
    }
  
    // invert avb
    if (n%3 == 0) { 
      ava = !ava;
      avb = !avb;
    }

    // keep rest low
    dtn = false;
    drn = false;
    }   
  
    // calc muscles
    for (int i = 0; i <= noSegments; i++) {
    if (i == 0) {
        cellie.head(dm[0], vm[0], drn, vrn, dm[1], vm[1], ava, avb);
    }
    else if (i == noSegments) {
        cellie.tail(dm[9], vm[9], dtn, vtn, dm[8], vm[8], ava, avb);
    }
    else {
       cellie.segment(dm[i], vm[i], dm[i-1], vm[i-1], dm[i+1], vm[i+1], ava, avb, i);
    }
    } 
  
    Serial.print(ava);
    Serial.print(",");
    Serial.print(avb);
    Serial.print(",");
    Serial.print(drn);
    Serial.print(",");
    Serial.print(dtn);
    Serial.print(",");
    Serial.print(vrn);
    Serial.print(",");
    Serial.print(vtn);
    Serial.print(",");
  
    // For data collection    
    for (int k = 0; k <= noSegments; k++) {
        Serial.print(dm[k]);
        Serial.print(",");
        Serial.print(vm[k]);  
        Serial.print(",");  
    }
         
  // update muscles  
    for (int j = 0; j <= noSegments; j++) {
        cellie.clockedge(dm[j], vm[j], j);
        dm[j] = cellie.next_dm[j];
        vm[j] = cellie.next_vm[j];       
        }
  
    n += 1;
      
    if (n == 18) {
      n = 0;  
      motion += 1;
    }

    Serial.println(motion); 
    

}
