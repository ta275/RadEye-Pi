#include <stdlib.h>
#include <stdint.h>


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

static int setStepMode(uint8_t val)
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
	snprintf(command, sizeof(command), "ticcmd --step-mode %s", mode);
	return run_command(command);
}

int main()
{
  printf("Setting step mode to 8.\n");
  int result = setStepMode(3);
  if (result) { return 1; }
  return 0;
}