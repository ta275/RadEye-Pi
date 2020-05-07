#include "TicDriver.h"

#include <unistd.h>
int main()
{
	const char vertical_sno [9] = "00295780";

	const char horizontal_sno [9] = "00286960";


	uint8_t step_mode = 0;

	uint32_t max_speed = 2000000 * (step_mode+1);
	uint32_t starting_speed = 0;
	uint32_t max_decel = 40000 * (step_mode+1);
	uint32_t max_accel = 40000 * (step_mode+1); 
	uint16_t current_limit = 1000;
	int32_t curr_pos = 0;

	int32_t full_vertical = 83;

	TicDriver* vertical = createTicDriver(vertical_sno, max_speed, starting_speed,
	 max_decel, max_accel, step_mode, current_limit, curr_pos);
	
	TicDriver* horizontal = createTicDriver(horizontal_sno, max_speed, starting_speed,
	 max_decel, max_accel, step_mode, current_limit, curr_pos);

	
	vertical->steps(vertical, full_vertical*(step_mode+1));

	sleep(2);
	vertical->steps(vertical, -1*full_vertical*(step_mode+1));
	
	// vertical->deenergize(vertical);

}
