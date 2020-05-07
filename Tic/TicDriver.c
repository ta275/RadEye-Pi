/*
 * TicDriver.h
 *
 * Created: 07-May-2020
 * Last Modified: 07-May-2020
 * Author : tejas_advait
 */


#include "TicDriver.h"
#include <stdlib.h>
#include <stdint.h>
// #include <string>


// Runs the given shell command.  Returns 0 on success, -1 on failure.
int run_command(const char * command)
{
  int result = system(command);
  if (result)
  {
    fprintf(stderr, "Command failed with code %d: %s\n", result, command);
    return -1;
  }
  return 0;
}

static int setStepMode(TicDriver* self, uint8_t val)
{
	self->step_mode = val;
	char command[1024];
	char mode[7];

	switch (val)
	{
		case 0: //Full-Step
  			// snprintf(command, sizeof(command), "ticcmd --step-mode full");
			snprintf(mode, sizeof(mode), "full");
			break;

		case 1:
			snprintf(mode, sizeof(mode), "half");
			break;

		case 2:
			snprintf(mode, sizeof(mode), "4");
			break;

		case 3:
			snprintf(mode, sizeof(mode), "8");
			break;

		case 4:
			snprintf(mode, sizeof(mode), "16");
			break;

		case 5:
			snprintf(mode, sizeof(mode), "32");
			break;

		case 6:
			snprintf(mode, sizeof(mode), "2_100p");
			break;

		default: 
			printf("Invalid step mode");
			return -1;
			break;
	}
	snprintf(command, sizeof(command), "ticcmd --step-mode %s", mode);
	return run_command(command);
}
static void setDir( BED* self, uint8_t dir){
	if (dir == 0x01) (self->DIR)->writeHigh(self->DIR);
	if (dir == 0x00) (self->DIR)->writeLow(self->DIR);
}

static void setMicro(BED* self, uint8_t res){
	if (res == 0x01){
		(self->MS1)->writeLow(self->MS1);
		(self->MS2)->writeLow(self->MS2);
		(self->MS3)->writeLow(self->MS3);
	}

	if (res == 0x02){
		(self->MS1)->writeHigh(self->MS1);
		(self->MS2)->writeLow(self->MS2);
		(self->MS3)->writeLow(self->MS3);
	}

	if (res == 0x04){
		(self->MS1)->writeLow(self->MS1);
		(self->MS2)->writeHigh(self->MS2);
		(self->MS3)->writeLow(self->MS3);
	}

	if (res == 0x08){
		(self->MS1)->writeHigh(self->MS1);
		(self->MS2)->writeHigh(self->MS2);
		(self->MS3)->writeLow(self->MS3);
	}

	if (res == 0x10){
		(self->MS1)->writeHigh(self->MS1);
		(self->MS2)->writeHigh(self->MS2);
		(self->MS3)->writeHigh(self->MS3);
	}

}


static void setEnable(BED* self, uint8_t val){
	if (val == 0x01) (self->ENABLE)->writeHigh(self->ENABLE);
	if (val == 0x00) (self->ENABLE)->writeLow(self->ENABLE);
}

static void setRst(BED* self, uint8_t val){
	if (val == 0x01) (self->RST)->writeHigh(self->RST);
	if (val == 0x00) (self->RST)->writeLow(self->RST);
}

static void setSleep(BED* self, uint8_t val){
	if (val == 0x01) (self->SLEEP)->writeHigh(self->SLEEP);
	if (val == 0x00) (self->SLEEP)->writeLow(self->SLEEP);
}

static void setRot(BED* self, int16_t val){ self->rot = val;}

static void step(BED* self){

	(self->STEP)->writeHigh(self->STEP);
	
	_delay_us(stpDelay);
	
	(self->STEP)->writeLow(self->STEP);
	
	_delay_us(stpDelay);
}

static void stepNum(BED* self, uint16_t numstp){

	for (uint16_t i = 0; i < numstp; i++){
		self->step(self);
	}
}


static void steps(BED* self, int16_t num, uint8_t res){
	if (self->getMicro(self) != res) self->setMicro(self, res);

	if (num < 0){
		if (self->getDir(self) != 0) self->setDir(self, 0);

		self->stepNum(self, (uint16_t) (-1*num));
	}


	if (num > 0){
		if (self->getDir(self) != 1) self->setDir(self, 1);

		self->stepNum(self, (uint16_t) num );
	}

}

static uint8_t getMicro(BED* self){
	if (!(self->MS1)->read(self->MS1)){

		if ((self->MS2)->read(self->MS2)) return 0x04;
		return 0x01;
	}

	if (!(self->MS2)->read(self->MS2)) return 0x02;

	if ((self->MS3)->read(self->MS3)) return 0x10;

	return 0x08;
}


static uint8_t getDir(BED* self) { return (self->DIR)->read(self->DIR); }


static uint8_t getEnable(BED* self){ return (self->ENABLE)->read(self->DIR); }

static uint8_t getRst(BED* self){ return (self->RST)->read(self->RST); }

static uint8_t getSleep(BED* self){ return (self->SLEEP)->read(self->SLEEP); }

static int16_t getRot(BED* self){ return self->rot; }



BED* createBED(GPIO* ENABLE, GPIO* MS1, GPIO* MS2, GPIO* MS3, GPIO* RST, GPIO* SLEEP, GPIO* STEP, GPIO* DIR){
	BED* driver = (BED*) malloc(sizeof(BED));

	if (driver == NULL) {
	/* Handle malloc failure */
	;
	}

	*driver = (BED){.ENABLE=ENABLE, .MS1=MS1, .MS2=MS2, .MS3=MS3, .RST=RST,

					.SLEEP=SLEEP, .STEP=STEP, .DIR=DIR, .setDir=setDir,

					.setMicro=setMicro, .setEnable=setEnable, .setRst=setRst,

					.setSleep=setSleep, .setRot=setRot,

					.step=step, .stepNum=stepNum, .steps=steps,

					.getMicro=getMicro, .getDir=getDir, .getEnable=getEnable,

					.getRst=getRst, .getSleep=getSleep, .getRot=getRot, .rot=0};


	(driver->ENABLE)->setAsOutput(driver->ENABLE);
	(driver->MS1)->setAsOutput(driver->MS1);
	(driver->MS2)->setAsOutput(driver->MS2);
	(driver->MS3)->setAsOutput(driver->MS3);
	(driver->RST)->setAsOutput(driver->RST);
	(driver->SLEEP)->setAsOutput(driver->SLEEP);
	(driver->STEP)->setAsOutput(driver->STEP);
	(driver->DIR)->setAsOutput(driver->DIR);

	(driver->ENABLE)->writeLow(driver->ENABLE);
	(driver->MS1)->writeLow(driver->MS1);
	(driver->MS2)->writeLow(driver->MS2);
	(driver->MS3)->writeLow(driver->MS3);
	(driver->RST)->writeHigh(driver->RST);
	(driver->SLEEP)->writeHigh(driver->SLEEP);
	(driver->STEP)->writeLow(driver->STEP);
	(driver->DIR)->writeLow(driver->DIR);

	return driver;
}

BED* copyBED(BED const* in){
	BED* out = malloc(sizeof(BED));

	*out = *in;
	return out;
}

void freeBED(BED* in){ free(in); }