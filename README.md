# FYP-Giving_the_brain_a_body
A digital double, or bio-double, of the C. Elegans biosystem. 
The objective of this project was to develop a soft robotic device that can replicate the locomotive system of a C. Elegans, by interfacing with a neural model developed in previous work. 

## MIT Sensor
The folder MIT sensor contains all code and data produced during the Magnetic Induction Tomography tests conducted on the actuator. 
This includes the code used to control the actuator, *valve_tests.ino*, and the code used to convert the induced voltage to distance, *plotting_distance.m*.

## Neural Models
The folder Neural Models contains the code developed in Arduino C++ replicating the original HDL model of the C. Elegans locomotive system created in previous work. 
Within this folder there are three models:
1. *neural_model_simple* contains the simplified model with respect to oscillations of the global synchronisation neurons and the stimulation neurons.
2. *neural_model_testbench* contains a replication of the original HDL model.
3. *neural_model_three* contains the simplified model with alterations such that the number of segments used in the model is limited to three, allowing control of the developed robot.
 
Data can be found in these folders recorded through a serial console, PuTTy, containing the status of the different neurons being controlled by these models at different stages for varying locomotive behaviours which were used to analyse the success of this neural model and its interface to the device.

## Pressure transducer
The folder Pressure transducer contains all code and data produced during the pressure tests for the device.
Here the folder *pressure_transducer* contains the code used to control the Arduino Nano connected to the pressure transducer.
All data was logged using the PuTTy serial console.

## Tracking
The folder Tracking contains all the code used when testing different visual processing techniques. 
Here the *object_tracking.ipynb* file contains the main code used for visual tracking of images and videos of the actuator.
All data on magnitude and angle of the actuator was recorded in *angle_len_data.csv*.

For additional information please contact Maria Petrou; mnp34@bath.ac.uk
    
