/*
Exemple de code glue pour deux t�ches p�riodiques
- une suppos�e rapide et frequente et qui doit s'appeler HighTask
- une suppos�e lente et moins fr�quente et qui doit s'appeler LowTask
- les p�riodes doivent �tre sp�cifi�es dans "periods.h"
	HIGH_PERIOD
	LOW_PERIOD
*/

#include "kernel.h"
#include "periods.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

/**** CODE GLUE, A MODIFIER/ADAPTER */
#include <string.h>  /* a cause du strlen plus bas */

/***** OSEK : NE PAS MODIFIER */
DeclareCounter(SysTimerCnt);
DeclareResource(lcd);
DeclareTask(LowTask);
DeclareTask(HighTask);

/* LEJOS OSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void)
{
	StatusType ercd; /* Increment OSEK Alarm System Timer Count */
	ercd = SignalCounter( SysTimerCnt );
	if( ercd != E_OK ){
		ShutdownOS( ercd );
	}
}
/******* FIN OSEK */

/* Initialisation et finalisations OSEK */
void ecrobot_device_initialize() {
	/*
	ICI : on peut mettre du code qui sera appel� automatiquement
	A�l'initialisation de la brique
	(ne rien mettre si pas n�cessaire)
	*/
}

void ecrobot_device_terminate() {
	/*
	ICI : on peut mettre du code qui sera appel� automatiquement
	à la l'extinction de la brique
	(ne rien mettre si pas n�cessaire)
	*/
}

/**** CODE GLUE, A MODIFIER/ADAPTER */

/*------------------------------
	D�clarations
--------------------------------
On met typiquement ici les d�clarations
de variables partag�es, de fonctions
accessoires etc.
------------------------------*/

int h_cpt;
int l_cpt;

/*------------------------------
	Initialisations
--------------------------------
On doit se d�brouiller pour que NOS initialisations
soient effectu�es. Comme on ne veut PAS TOUCHER
une seule ligne au code OSEK, on utilise un kernel_cfg.c
modifi�, o� une nouvelle fonction, "usr_init()", est
appel�e � l'initialisation du syst�me.
CETTE FONCTION DOIT �TRE D�FINIE
(vide �ventuellement)
------------------------------*/

/* utilitaire : affichage d'une variable.
L'affichage DOIT �tre r�alis� en exclusion
mutuelle.
D'o� l'utilisation du verrou "lcd"
fourni par le noyau temps r�el (cf. kernel_cfg.h)
*/
void show_var(char* what, int line, int var) {
	display_goto_xy(0, line);
	display_string(what);
	display_goto_xy(strlen(what)+1, line);
	display_int(var, 5);
	display_update();
}

void usr_init(void) {
	GetResource(lcd);
	h_cpt = 0;
	l_cpt = 0;

	// Mettre ici des initialisations �ventuelles
	int cpt = 0;
	show_var("usr_int",4,0);

	// Du code sequentiel
	//show_var("Calibrage Blanc",3,0);
	while (1) {
		cpt++;
		show_var("cpt",5,cpt);
		if ( ecrobot_is_ENTER_button_pressed()) break;
		systick_wait_ms(500);
	}
	//systick_wait_ms(1000);
	//show_var("calibrage noir ",4,0);
	//while (ecrobot_is_ENTER_button_pressed() == 0) { y++; }
	//systick_wait_ms(1000);
	ReleaseResource(lcd);
}

/*------------------------------
  Definitions des taches
--------------------------------
Elles doivent :
- �tre d�clar�es par la macro TASK
- le code doit se terminer par la macro TerminateTask()
------------------------------*/

TASK(HighTask) {

	h_cpt++;
	show_var("high", 0, h_cpt);

	/* OSEK : FINALISATION TASK, NE PAS TOUCHER */
	TerminateTask();
}

TASK(LowTask) {

	l_cpt++;
	show_var("low ", 1, l_cpt);

	/* OSEK : FINALISATION TASK, NE PAS TOUCHER */
	TerminateTask();
}
