#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#include "Controller.h"

#define RIGHT_WHEEL_PORT NXT_PORT_A
#define LEFT_WHEEL_PORT NXT_PORT_B
#define RIGHT_LIGHT_SENSOR NXT_PORT_S1
#define LEFT_LIGHT_SENSOR NXT_PORT_S2

// from 0-1023 to 0-100
#define LIGHT_SENSOR_TO_PERCENTAGE(X) ((X)/10.23)

/* OSEK declarations */
DeclareCounter(SysTimerCnt);
DeclareTask(Task1);

/* LEJOS OSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void) {
	StatusType ercd;

	ercd = SignalCounter(SysTimerCnt); /* increment OSEK alarm counter */
	if(ercd != E_OK) {
		ShutdownOS(ercd);
	}
}

void usr_init(void) {
	// does nothing
}

void ecrobot_device_initialize() {
	Controller_reset();

	ecrobot_set_light_sensor_active(RIGHT_LIGHT_SENSOR);
	ecrobot_set_light_sensor_active(LEFT_LIGHT_SENSOR);
}

void ecrobot_device_terminate() {
	ecrobot_set_light_sensor_inactive(RIGHT_LIGHT_SENSOR);
	ecrobot_set_light_sensor_inactive(LEFT_LIGHT_SENSOR);

	ecrobot_set_motor_speed(RIGHT_WHEEL_PORT, 0);
	ecrobot_set_motor_speed(LEFT_WHEEL_PORT, 0);
}

void output_motor(U32 port, _real speed) {
	U8 speed_percent;

	if (speed > 100.0) {
		speed_percent = 100;
	} else if (speed < -100.0) {
		speed_percent = -100;
	} else {
		speed_percent = speed;
	}

	nxt_motor_set_speed(port, speed_percent, 0); // brake mode = 0 (float?)
}

void Controller_O_u_d(_real ud) {
	output_motor(RIGHT_WHEEL_PORT, ud);	
}

void Controller_O_u_g(_real ug) {
	output_motor(LEFT_WHEEL_PORT, ug);
}

TASK(Task1) {
	U16 raw_sensor_right;
	U16 raw_sensor_left;

	// returns 0 to 1023
	raw_sensor_right = ecrobot_get_light_sensor(RIGHT_LIGHT_SENSOR);
	raw_sensor_left = ecrobot_get_light_sensor(LEFT_LIGHT_SENSOR);

	// Controller_I_C* expects value from 0 to 100
	Controller_I_Cd(LIGHT_SENSOR_TO_PERCENTAGE(raw_sensor_right));
	Controller_I_Cg(LIGHT_SENSOR_TO_PERCENTAGE(raw_sensor_left));

	Controller_step();

	TerminateTask(); // don't change
}
