# Who is Howard the drone ?
Drones are getting more and more commonplace nowadays, and new uses appear every day in extremely varied fields. Howard is a rescue drone based on the AR Drone 2.0 produced by Parrot.  
The purpose of this project is to facilitate the location and rescue of lost hikers. In an avalanche situation, time is the most critical issue as past 15min trapped under the snow, the victim has very low chances of survival. The Howard Project is meant to considerably decrease the time needed to locate the victims.  
To be localizable by the drone, said victims have to carry a beacon emitting a radio signal at the frequency of 1.2 GHz. The drone is equipped with a directive antenna specifically tuned to the same frequency. When the drone is launched, it searches for the beacon by following a nautilus-like trajectory: it circles around the beacon while getting closer. The goal was to reach a distance of less than 4m away from the beacon. To reach these objectives:
- A specific control program has been developed to pilot the drone. 
- A homemade Yagi antenna has been built and attached to the drone, and is linked to a Software Defined Radio dongle, plugged into the AR Drone’s USB port.

The radio signal collected by the antenna is used to determine the direction of the beacon, which will be used by the trajectory algorithm to bring the drone closer to the target.  
In order to test the trajectory algorithm, a simulator has also been implemented. This simulator can be used on two modes: a complete simulation and a simulation of the signal power measurements only.  
An overview of the project is available on our webpage : https://sites.google.com/site/projetsecinsa/projets-2015-2016/project

# Parrot AR Drone 2.0 drescription
    Processeur ARM Cortex A8 Cadencé @1 GHz
    DSP Vidéo Cadencé @800 MHz
    128 Mo de RAM DDR2 à 200 MHz
    128 Mo de Flash
    Wi-Fi b/g/n
    USB high speed (2.0)
    Linux OS 2.6.32

