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




static int setStepMode(uint32_t sno, uint8_t val)
{
	// self->step_mode = val;
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
	snprintf(command, sizeof(command), "ticcmd -d %d --step-mode %s",sno, mode);
	return run_command(command);
}

int tic_set_target_position(uint32_t sno, int32_t target)
{
  char command[1024];
  snprintf(command, sizeof(command), "ticcmd --exit-safe-start -d %d --position %d", sno, target);
  return run_command(command);
}

int halt_and_set_position(uint32_t sno, int32_t pos)
{
  char command[1024];
  snprintf(command, sizeof(command), "ticcmd -d %d --halt-and-set-position %d  ", sno, pos);
  return run_command(command);
}

int main()
{
	uint32_t vertical_sno = 00295780;
	uint32_t horizontal_sno = 00286960;
	printf("Setting step mode to 1.\n");
	int result1 = setStepMode(vertical_sno, 0);
	int result2 = setStepMode(horizontal_sno, 0);
	halt_and_set_position(vertical_sno, 0);
	halt_and_set_position(horizontal_sno, 0);


	tic_set_target_position(vertical_sno, 81);
	tic_set_target_position(horizontal_sno, 10);

	if (result1 && result2) { return 1; }
	return 0;
}