/*
 * PiComm.h
 *
 * Created: 14-Feb-2020
 * Last Modified: 14-Feb-2020
 * Author : tejas_advait
 */

#pragma once

#include <stdint.h>

#include "PiGPIO.h"



typedef struct PiComm {
    PiGPIO* ENPIN; //Enable Pin
    PiGPIO* DNPIN; //Done Pin

    PiGPIO* DATPORT[8]; //Data Port

    uint8_t numCycles; //Number of cycles
    

    uint8_t (*readDn)(struct PiComm*); //Read done pin
    void (*writeSingle)(struct PiComm*); //Write the data port once
    void (*writeCycle)(struct PiComm*); //Write the data port numCycles times
    void (*setEnHigh)(struct PiComm*); //Set enable pin to high
    void (*setEnLow)(struct PiComm*); //Set enable pin to low
    uint8_t DATASINGLE; //Single data for writing
    uint8_t* DATA; //Cycle data for writing

  } PiComm;




PiComm* createPiComm(PiGPIO* ENPIN, PiGPIO* DNPIN, PiGPIO** DATPORT, uint8_t numCycles, uint8_t* DATA);

PiComm* copyPiComm(PiComm const* in);

void freePiComm(PiComm* in);