
/*

Exemple de code glue pour deux tâches périodiques HARMONIQUES
AVEC COMMUNICATION

- une supposée rapide et frequente et qui doit s'appeler HighTask
  qui fait tourner un noeud lustre "high"
- une supposée lente et moins fréquente et qui doit s'appeler LowTask
  qui fait tourner un noeud lustre "low"
- les périodes doivent être spécifiés dans kernel_cfg.h avec les macros :
     HIGH_PERIOD
     LOW_PERIOD
  qui doivent être harmoniques : LOW_PERIOD = n * HIGH_PERIOD
*/

#include "kernel.h"
#include "periodes.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

/**** CODE GLUE, A MODIFIER/ADAPTER */
/* Ici : inclusion du header Lustre */
#include <string.h>  /* a cause du strlen plus bas */
#include "low.h"
#include "high.h"

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
      ICI : on peut mettre du code qui sera appelÃ© automatiquement
            Ã  l'initialisation de la brique
      (ne rien mettre si pas nÃ©cessaire)
   */
}

void ecrobot_device_terminate() {
   /*
      ICI : on peut mettre du code qui sera appelÃ© automatiquement
            Ã  la l'extinction de la brique
      (ne rien mettre si pas nÃ©cessaire)
   */
}

/**** CODE GLUE, A MODIFIER/ADAPTER */
/*

REMARQUE :

On utilise l'option "-ctx-static", donc pas de parametres aux "methodes" Lustre

*/


/*------------------------------
	Déclarations
--------------------------------
  On met typiquement ici les déclarations
de variables partagées, de fonctions
accessoires etc.
------------------------------*/

/*
	Pour gérer les communications :
*/

_integer H2L;       // buffer High -> Low
_integer L2H[2];    // double-buffer Low -> High
_integer L2Hindex;  // 0 ou 1 : indique dans quelle
                    // case du double-buffer Low doit écrire

_integer Hcpt;      // compte les "instants" High

//Le ratio des periodes :
//(le compilateur se charge du calcul statiquement)
#define PRATIO ((int)(LOW_PERIOD/HIGH_PERIOD))

/*------------------------------
	Initialisations
--------------------------------
  On doit se débrouiller pour que NOS initialisations
soient effectuées. Comme on ne veut PAS TOUCHER
une seule ligne au code OSEK, on utilise un kernel_cfg.c
modifié, où une nouvelle fonction, "usr_init()", est
appelée à l'initialisation du système.
Cette fonction doit être définie ici.
------------------------------*/

void usr_init(void) {
	high_init();
	low_init();
	//Index de la case où L ecrira la premiere fois
	L2Hindex = 0;
	//Il faut initialiser le registre où H lira la premiere fois
	//c'est-a-dire celui ou L n'ecrit pas !
	L2H[1] = 0;
}

/* Procédure de sortie */
/**
 * Affiche a l'ecran "what var"
 */
void show_var(char* what, int line, int var) {
   GetResource(lcd);
   display_goto_xy(0, line);
   display_string(what);
   display_goto_xy(strlen(what)+1, line);
   display_int(var, 5);
   display_update();
   ReleaseResource(lcd);
}


void high_O_s(_integer val){
	show_var("high_O_s", 1, val);
}

void high_O_h2l(_integer val){
	//Communication H -> L 
	//si Hcpt == 0, on modifie H2L, on est sur qu'il sera lu
	//par Low avant le prochain Lupto !
	show_var("high_O_h2l", 2, val);
	if (Hcpt == 0) {
		H2L = val;
	}
	//sinon rien
}

void low_O_s(_integer val){
	show_var("low_O_s", 4, val);
}

void low_O_l2h(_integer val){
	//Communication L -> H
	//écrit dans la case du buffer désignée par L2Hindex :
	L2H[L2Hindex] = val;
	show_var("low_O_l2h", 5, val);
}

/*------------------------------
  Definitions des taches 
--------------------------------
Elles doivent :
- être déclarées par la macro TASK
- le code doit se terminer par la macro TerminateTask()
------------------------------*/


TASK(HighTask) {
	/* Positionnement des entrées */
	high_I_e( ecrobot_get_touch_sensor(NXT_PORT_S1) );

	/* On lit toujours dans la case opposée à L2Hindex */
	high_I_l2h(L2H[!L2Hindex]);

	/* Appel du step */
	high_step();

	/* OÙ on en est avec la tache Low ? */
	if (Hcpt  == 0) {
		/*
			Low va démarer un cycle juste apres High ...
		   on "swape"  le double buffer
		*/
		L2Hindex = !L2Hindex;
	}
	/* et on fait avancer le compteur ... */
	Hcpt = (Hcpt+1) % PRATIO;
	
	/* OSEK : FINALISATION TASK, NE PAS TOUCHER */
	TerminateTask();
}
	
	

TASK(LowTask) {

	/* Positionnement des entrées */
	low_I_e( ecrobot_get_touch_sensor(NXT_PORT_S2) );

	// Com H -> L, on lit toujours la valeur courante de H2L
	low_I_h2l(H2L);

	/* Appel du step */
	low_step();

	/* OSEK : FINALISATION TASK, NE PAS TOUCHER */
	TerminateTask();
}

