/*
 * PiComm.c
 *
 * Created: 14-Feb-2020
 * Last Modified: 14-Feb-2020
 * Author : tejas_advait
 */

#include "PiComm.h"
#include <stdlib.h>
#include <stdint.h>
#include "misc.h"


static uint8_t readDn(PiComm* self){ return (self->DNPIN)->read(self->DNPIN); }


static void writeSingle(PiComm* self){
	self->setEnLow(self);

	delayMicrosecondsHard(500000);

	while(!self->readDn(self)) {;}

	delayMicrosecondsHard(500000);

	uint8_t i;
	uint8_t bit;

	for (i = 0; i < 8; i++){
		bit = ((self->DATASINGLE) >> i) & 0x01;

		if (bit){ (self->DATPORT[i])->writeHigh(self->DATPORT[i]); }

		if (!bit){ (self->DATPORT[i])->writeLow(self->DATPORT[i]); }

	}

	self->setEnHigh(self);

	delayMicrosecondsHard(500000);

	while (self->readDn(self)) {;}
	
	delayMicrosecondsHard(500000);
}



static void writeCycle(PiComm* self){ 
	// assert(self->isDat(self) == 1);

	uint8_t i;

	for (i = 0; i < self->numCycles; i++){
		self->DATASINGLE = self->DATA[i];
		self->writeSingle(self);
	}

}

static void setEnHigh(PiComm* self){ (self->ENPIN)->writeHigh(self->ENPIN); }

static void setEnLow(PiComm* self){ (self->ENPIN)->writeLow(self->ENPIN); }



PiComm* createPiComm(PiGPIO* ENPIN, PiGPIO* DNPIN, PiGPIO** DATPORT, uint8_t numCycles, uint8_t* DATA){
	PiComm* cbus = (PiComm*) malloc(sizeof(PiComm));

	if (cbus == NULL) {
	/* Handle malloc failure */
	;
	}

	*cbus = (PiComm){ .ENPIN=ENPIN, .DNPIN=DNPIN,
		.DATPORT=DATPORT, .numCycles=numCycles,
		.setEnHigh=setEnHigh, .setEnLow=setEnLow,
		.writeSingle=writeSingle, .writeCycle=writeCycle,
		.readDn=readDn, .DATASINGLE=0, .DATA=DATA };

	(cbus->DNPIN)->setAsInput(cbus->DNPIN);
	
	
	(cbus->ENPIN)->setAsOutput(cbus->ENPIN);
	cbus->setEnLow(cbus);

	uint8_t i;
	for (i = 0; i < 8; i++){
		(cbus->DATPORT[i])->setAsOutput(cbus->DATPORT[i]);
	}

	return cbus;
}

PiComm* copyPiComm(PiComm const* in){
	PiComm* out = malloc(sizeof(PiComm));

	*out = *in;
	return out;
}

void freePiComm(PiComm* in){ free(in); }
