/*
 * PiGPIO.h
 *
 * Created: 12-Feb-20 10:00:12 AM
 * Author : ta275
 *
 * Description: Use the PiGPIO type and associated methods for manipulating GPIO pins.
 */ 

#pragma once
#include <stdint.h>

typedef struct PiGPIO{

	uint32_t PINNUM;			/// Pin number of the GPIO pin

	volatile uint32_t* setupGPIO;

	void (*setAsOutput)(struct PiGPIO*);	/// Set GPIO pin as output

	void (*setAsInput)(struct PiGPIO*);	/// Set GPIO pin as input

	void (*writeHigh)(struct PiGPIO*);	/// Write high to the GPIO pin (GPIO pin must be declared as output before this method is called)

	void (*writeLow)(struct PiGPIO*);		/// Write low to the GPIO pin (GPIO pin must be declared as output before this method is called)

	uint8_t (*read)(struct PiGPIO*);		/// Read the GPIO pin value

} PiGPIO;


PiGPIO* createPiGPIO(uint32_t PINNUM);	/// Create a GPIO pin

PiGPIO* copyPiGPIO(PiGPIO const* in);													/// Copy a GPIO pin

void freePiGPIO (PiGPIO* in);														/// Free (delete) a GPIO pin
