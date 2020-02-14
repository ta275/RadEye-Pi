/*
 * PiCommTest1.c
 *
 * Created: 14-Feb-2020
 * Last Modified: 14-Feb-2020
 * Author : tejas_advait
 */

#include "PiGPIO.h"
#include "PiComm.h"

#include <sys/time.h>
#include <time.h>

void delayMicrosecondsHard (unsigned int howLong)
{
  struct timeval tNow, tLong, tEnd ;

  gettimeofday (&tNow, NULL) ;
  tLong.tv_sec  = howLong / 1000000 ;
  tLong.tv_usec = howLong % 1000000 ;
  timeradd (&tNow, &tLong, &tEnd) ;

  while (timercmp (&tNow, &tEnd, <))
    gettimeofday (&tNow, NULL) ;
}

void delay (unsigned int howLong)
{
  struct timespec sleeper, dummy ;

  sleeper.tv_sec  = (time_t)(howLong / 1000) ;
  sleeper.tv_nsec = (long)(howLong % 1000) * 1000000 ;

  nanosleep (&sleeper, &dummy) ;
}


int main(){

	PiGPIO* ENPIN = createPiGPIO(26);
	PiGPIO* DNPIN = createPiGPIO(19);

	PiGPIO* DP7 = createPiGPIO(21);
	PiGPIO* DP6 = createPiGPIO(20);
	PiGPIO* DP5 = createPiGPIO(16);
	PiGPIO* DP4 = createPiGPIO(12);
	PiGPIO* DP3 = createPiGPIO(1);
	PiGPIO* DP2 = createPiGPIO(7);
	PiGPIO* DP1 = createPiGPIO(8);
	PiGPIO* DP0 = createPiGPIO(25);

	PiGPIO* DATPORT[8] = {DP0, DP1, DP2, DP3, DP4, DP5, DP6, DP7};

	uint8_t numCycles = 10;

	uint8_t DATA[numCycles];

	uint8_t i;

	for (i = 0; i<numCycles; i++){
		DATA[i] = i+1;
	}

	PiComm* comm = createPiComm(ENPIN, DNPIN, DATPORT, numCycles, DATA);


	delay(2000);

	for (i = 0; i < comm->numCycles; i++){
		comm->DATASINGLE = comm->DATA[i];
		comm->writeSingle(comm);
		delay(1000);
	}
	return 0;
}