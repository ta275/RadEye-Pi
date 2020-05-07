/*
 * TicDriver.h
 *
 * Created: 07-May-2020
 * Last Modified: 07-May-2020
 * Author : tejas_advait
 */

#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 
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
 
// Sets the target position, returning 0 on success and -1 on failure.
int tic_set_target_position(int32_t target)
{
  char command[1024];
  snprintf(command, sizeof(command), "ticcmd --exit-safe-start --position %d", target);
  return run_command(command);
}
 
int main()
{
  printf("Setting target position to 800.\n");
  int result = tic_set_target_position(800);
  if (result) { return 1; }
  return 0;
}

typedef struct  TicDriver{

	uint32_t serial_no;
	
	uint32_t max_speed;
	uint32_t starting_speed;
	uint32_t max_decel;
	uint32_t max_accel;
	
	uint8_t step_mode;
	uint16_t current_limit;

	int32_t curr_pos;
	int32_t target_pos;


	int (*setStepMode)(struct TicDriver*, uint8_t val);	/// Set step mode

	int (*setCurrentLimit)(struct TicDriver*, uint16_T val);

	int (*setTargetPos)(struct TicDriver*, int32_t val);

	int (*setCurrPos)(struct TicDriver*, int32_t val);

	int (*setMaxDecel)(struct TicDriver*, uint32_t val);

	int (*setMaxAccel)(struct TicDriver*, uint32_t val);

	int (*setStartingSpeed)(struct TicDriver*, uint32_t val);

	int (*setMaxSpeed)(struct TicDriver*, uint32_t val);



} TicDriver;


TicDriver* createTicDriver(	uint32_t serial_no, uint32_t max_speed, uint32_t starting_speed, uint32_t max_decel, uint32_t max_accel, uint8_t step_mode, uint16_t current_limit, int32_t curr_pos);

TicDriver* copyTicDriver(TicDriver const* in);

void TicDriver(TicDriver* in);