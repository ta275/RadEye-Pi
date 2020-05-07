#include "TicDriver.h"

#include <unistd.h>
int main()
{
	const char vertical_sno [9] = "00295780";

	const char horizontal_sno [9] = "00286960";

	uint32_t max_speed = 4000000;
	uint32_t starting_speed = 0;
	uint32_t max_decel = 40000;
	uint32_t max_accel = 40000; 
	uint8_t step_mode = 0;
	uint16_t current_limit = 1000;
	int32_t curr_pos = 0;

	TicDriver* vertical = createTicDriver(vertical_sno, max_speed, starting_speed,
	 max_decel, max_accel, step_mode, current_limit, curr_pos);
	
	TicDriver* horizontal = createTicDriver(horizontal_sno, max_speed, starting_speed,
	 max_decel, max_accel, step_mode, current_limit, curr_pos);

	vertical->steps(vertical, 83);

	sleep(2);

	vertical->steps(vertical, -83);

	sleep(2);
	
	vertical->deenergize(vertical);

}
