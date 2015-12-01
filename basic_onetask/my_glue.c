
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#include "Controller.h"

/**** CODE GLUE, A MODIFIER/ADAPTER */

/*
	ICI : inclure d'éventuels header
   e.g. string.h, math.h etc.
*/
#include <string.h>

#define RIGHT_WHEEL_PORT NXT_PORT_A
#define LEFT_WHEEL_PORT NXT_PORT_B
#define RIGHT_LIGHT_SENSOR NXT_PORT_S1
#define LEFT_LIGHT_SENSOR NXT_PORT_S2

// from 0-1023 to 0-100
#define LIGHT_SENSOR_TO_PERCENTAGE(X) ((X)/10.23)

/***** OSEK : NE PAS MODIFIER */
/* OSEK declarations */
DeclareCounter(SysTimerCnt);
DeclareTask(Task1);

/* LEJOS OSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void)
{
  StatusType ercd;

  ercd = SignalCounter(SysTimerCnt); /* Increment OSEK Alarm Counter */
  if(ercd != E_OK)
  {
    ShutdownOS(ercd);
  }
}
/******* FIN OSEK */

/* Initialisation et finalisations OSEK */
void ecrobot_device_initialize() {

	/*
		ICI : on peut mettre du code qui sera appelé automatiquement
		      à l'initialisation de la brique
		(ne rien mettre si pas nécessaire)
	exemple de code:
   ecrobot_set_light_sensor_active(NXT_PORT_S1);
   ecrobot_set_light_sensor_active(NXT_PORT_S2);
	*/


}

void ecrobot_device_terminate() {

	/*
		ICI : on peut mettre du code qui sera appelé automatiquement
		      à la l'extinction de la brique
		(ne rien mettre si pas nécessaire)
	exemple de code:
   ecrobot_set_light_sensor_inactive(NXT_PORT_S1);
   ecrobot_set_light_sensor_inactive(NXT_PORT_S2);
	*/
}

/**** CODE GLUE, A MODIFIER/ADAPTER */

/** ICI, VOTRE CODE C accessoire (variables globales, utilitaire etc
	exemple d'utilitaire: affchage d'un nom de variable et de sa valeur
   sur une ligne donnée ...
**/

void output_motor(U32 port, _real speed) {
	int speed_percent = speed;

	if (speed > 100.0) {
		speed_percent = 100;
	} else if (speed < -100.0) {
		speed_percent = -100;
	}

	nxt_motor_set_speed(port, speed_percent, 0); // brake mode = 0 (float?)
}

void Controller_O_u_d(_real ud) {
	output_motor(RIGHT_WHEEL_PORT, ud);	
}

void Controller_O_u_g(_real ug) {
	output_motor(LEFT_WHEEL_PORT, ug);
}

void show_var(char* varname, int line, int value) {
   display_goto_xy(0, line);
   display_string(varname);
   display_goto_xy(strlen(varname)+1, line);
   display_int(value, 5);
   display_update();
}

void usr_init(void) {
	ecrobot_set_light_sensor_active(RIGHT_LIGHT_SENSOR);
	ecrobot_set_light_sensor_active(LEFT_LIGHT_SENSOR);
}

TASK(Task1)
{
	U16 sensor_right;
	U16 sensor_left;

	// return 0 to 1023
	sensor_right = ecrobot_get_light_sensor(RIGHT_LIGHT_SENSOR);
	sensor_left = ecrobot_get_light_sensor(LEFT_LIGHT_SENSOR);

	Controller_I_Cd(LIGHT_SENSOR_TO_PERCENTAGE(sensor_right));
	Controller_I_Cg(LIGHT_SENSOR_TO_PERCENTAGE(sensor_left));

	TerminateTask(); // don't change
}
