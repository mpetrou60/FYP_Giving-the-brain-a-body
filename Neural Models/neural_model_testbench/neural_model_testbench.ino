/*****************************************************************************
 * FILE NAME: neural_model                                                   *
 *                                                                           * 
 * PURPOSE: This is the main file for controlling the device, replicating    *
 *          the testbench developed in previosu work,using ModelSim. The     *
 *          device will follow the locomotive behaviour of the C. Elegans    *
 *          which has been defined in a class in the Cellie.h file. This     *
 *          class is the arduino implementation of the C. Elegans locomotive *
 *          event-based model developed in previous work on System Verilog.  * 
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

// look into arduino library
// make relay module class? - pwm???
// control pump class?
// read pressure transducer class? - feedback?

// *** VALVES ****************************************************************
// (LED = placeholder)
//#define valve1Pin 12
//#define valve2Pin 13

// *** PUMP ******************************************************************
#define pump1Pin A5 // check pin
#define pump2Pin A3 // check pin

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

// *** CLOCK *****************************************************************
unsigned long delayClock = 0;   // the time the delay started

int counterIc = 0;   // replace 10000000 ns - aka 20000 clock cycles; and replace 1000 ns - aka 2 clock cycles
int counterAvx = 0;  // replace 180000 ns - aka 3600 clock cycles; 1000 ns - aka 2 clock cycles; 1790000 ns - aka 3580 clock cycles
int counterVDxn = 0; // replace 1200000 ns - aka 2400 clock cycles

int avxi = 0;
int vdxi = 0;
int ici = 0;

bool myClock = false;
bool posClockedge = false;
bool reset = false;

// *** SETTING UP THE NEURAL MODEL *********************************************
// motion generation
bool mv_fwd = false;
bool mv_coil = false;
bool avx = false;
bool dxn = false;
bool vxn = false;

// for multiple segments
int noSegments = 9; // 10 segments, because subscript 0 (0-9)
int i = 0;

// Call header file containing neural network class
#include "Cellie.h"

// Define neural network instance for main script
Cellie cellie(pump1Pin, pump2Pin);

void setup() {
  Serial.begin(9600);
  Serial.println("Testbench Tests");
  
  cellie.init();                // initialises the built-in LED pin as an output.
  cellie.reset();               // resets the state of cell/neuron variables of the Cellie class.
  cellie.clockedge(0, 0, 0);    // sets state of all cell/neuron variables to those that have been resetted
  
  delayClock = micros(); // start delay
  dxn = false;
  vxn = !dxn;

  // Label for data collection
  Serial.print("Clock");
  Serial.print(",");
  Serial.print("move forward");
  Serial.print(",");
  Serial.print("move coil");
  Serial.print(",");
  Serial.print("reset");
  Serial.print(",");
  Serial.print("avx");
  Serial.print(",");
  Serial.print("dxn");
  Serial.print(",");
  Serial.print("vxn");
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
  // *** Clock generation: *******************************************************
  if ((micros() - delayClock) >= 1) { // 500 ns (0.0005 ms)

    delayClock = micros();
    myClock = !myClock;
    if (myClock == true) {
      posClockedge = true;
    }
        
    counterIc += 1;  // increment to 20000 clock cycles or 2 clock cycles
    counterAvx += 1; // increment to 360 clock cycles or 2 clock cycles or 358 clock cycles
    counterVDxn += 1;  // increment to 2400 clock cycles
  }
  else {
    posClockedge = false;
  }

  // *** Set Initial condition *****************************************************
  // repeat five at posedge clock
  if ((posClockedge == true) && (counterIc >= 400) && (ici == 0)) { // 10000000 ns (10ms) => x20000 clock  
    counterIc = 0;
    reset = false;
    mv_fwd = true;
    mv_coil = false;
    ici += 1;
  }
  else if ((posClockedge == true) && (counterIc >= 400) && (ici == 1)) { // 10000000
    counterIc = 0;
    mv_fwd = false;
    ici += 1;
  }
  else if ((posClockedge == true) && (counterIc >= 400) && (ici == 2)) { // 10000000
    counterIc = 0;
    mv_fwd = true;
    ici += 1;
  }
  else if ((posClockedge == true) && (counterIc >= 400) && (ici == 3)) { // 10000000
    counterIc = 0;
    mv_fwd = false;
    ici += 1;
  }
  else if ((posClockedge == true) && (counterIc >= 400) && (ici == 4)) { // 10000000
    counterIc = 0;
    reset = true;
    ici += 1;
  }
  else if ((posClockedge == true) && (counterIc >= 5) && (ici == 5)) { // 1000 => x2 clock
    counterIc = 0;
    reset = false;
    mv_coil = true;
    ici = 0;
  }

  Serial.print(myClock);          //the first variable for plotting
  Serial.print(",");              //seperator
  Serial.print(mv_fwd);           //the second variable for plotting including line break
  Serial.print(",");              //seperator
  Serial.print(mv_coil);          //the third variable for plotting including line break
  Serial.print(",");              //seperator
  Serial.print(reset);
  Serial.print(",");              //seperator

  // *** Setup motion generation: *************************************************
  // DxN and VxN DELAY
  if (counterVDxn >= 60) { // 1200000 ns => x2400 clock
    counterVDxn = 0;
    dxn = !dxn;
    vxn = !dxn;
  }
  else {
 }
  
  // AVx DELAY
  if ((counterAvx >= 2) && (avxi == 0)) { // 1000 ns => x2 clock
    counterAvx = 0;
    avxi += 1;
    avx = false; 
  }
  else if ((counterAvx >= 18) && (avxi == 1)) { // 179000 ns => x358 clock
    counterAvx = 0;
    avx = true; 
    avxi = 0;
  }
  
  // always_comb begin 
  if (mv_fwd == true) {                // forwards motion
    ava = false;
    avb = avx;
    drn = dxn;
    dtn = false;
    vrn = vxn;
    vtn = false;
  }
  else if (mv_coil & !mv_fwd == true) { // coiling behaviour
    ava = avx;
    avb = avx;
    vrn = vxn;
    drn = false;
    vtn = vxn;
    dtn = false;
  }
  else {                               // backwards motion
    ava = avx;
    avb = false;
    drn = false;
    dtn = dxn;
    vrn = false;
    vtn = vxn;
  }

  // For data collection
  Serial.print(avx);
  Serial.print(",");
  Serial.print(dxn);
  Serial.print(",");
  Serial.print(vxn);
  Serial.print(",");
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
    
  // *** SEGMENT SET-UP (Device Under Test) ******************************************************
  if (reset == true) {
      cellie.reset();
  }

  else {
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
  }

  // For data collection    
  for (int k = 0; k <= noSegments; k++) {
      Serial.print(dm[k]);
      Serial.print(",");
      Serial.print(vm[k]);  
      Serial.print(",");  
  }
  
  Serial.println(".");

  // update on clock posedge
  for (int j = 0; j <= noSegments; j++) {
  if (posClockedge == true) {
      cellie.clockedge(dm[j], vm[j], j);
      dm[j] = cellie.next_dm[j];
      vm[j] = cellie.next_vm[j];
      }
   }
  
}
