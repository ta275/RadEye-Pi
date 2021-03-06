#include "TicDriver.h"
#include <math.h>
#include <unistd.h>
int main()
{
	const char vertical_sno [9] = "00295780";


	uint8_t step_mode = 3;
	uint8_t mult = (uint8_t) pow(2, (double)step_mode);

	uint32_t max_speed = 2000000 * mult;
	uint32_t starting_speed = 0;
	uint32_t max_decel = 40000 * mult;
	uint32_t max_accel = 40000 * mult; 
	uint16_t current_limit = 1000;
	int32_t curr_pos = 0;

	int32_t full_vertical = 83;

	TicDriver* vertical = createTicDriver(vertical_sno, max_speed, starting_speed,
	 max_decel, max_accel, step_mode, current_limit, curr_pos);

	vertical->steps(vertical, 3);

}