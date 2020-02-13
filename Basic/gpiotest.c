#include "PiGPIO.h"
#include <unistd.h>

int main(){
	PiGPIO* pin19 = createPiGPIO(19);
	
	pin19->setAsOutput(pin19);


	while (1){
		pin19->writeHigh(pin19);

		sleep(1);

		pin19->writeLow(pin19);

		sleep(1);
	}


	return 0;

}