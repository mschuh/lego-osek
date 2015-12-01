/********
* ec2c version 0.67
* c file generated for node : Controller 
* context   method = STATIC
* ext call  method = PROCEDURES
********/
/* This program needs external declarations */
#define _Controller_EC2C_SRC_FILE
#include "Controller.h"

#define kp_teta 2.5 // 2
#define ki_teta 0.05
#define pi 3.1415

/*--------
 * the following ``constants'' must be defined:
extern _real pi;
extern _real kp_teta;
extern _real ki_teta;
--------*/

/*--------
Internal structure for the call
--------*/
typedef struct  {
   
   //INPUTS
   _real _Cg;
   _real _Cd;
   _real _Co;
   //OUTPUTS
   _real _u_d;
   _real _u_g;
   //REGISTERS
   _real M52;
   _boolean M52_nil;
   _boolean M15;
   _boolean M15_nil;
   _boolean M33;
   _boolean M33_nil;
   _boolean M27;
   _boolean M27_nil;
   _boolean M10;
   _boolean M10_nil;
   _boolean M7;
} Controller_ctx;

// Single Static Context
static Controller_ctx ctx;
/*--------
Output procedures must be defined,
Input procedures must be used:
--------*/
void Controller_I_Cg(_real V){
   ctx._Cg = V;
}
void Controller_I_Cd(_real V){
   ctx._Cd = V;
}
void Controller_I_Co(_real V){
   ctx._Co = V;
}
extern void Controller_O_u_d(_real);
extern void Controller_O_u_g(_real);
#ifdef CKCHECK
extern void Controller_BOT_u_d();
extern void Controller_BOT_u_g();
#endif
/*--------
Internal reset input procedure
--------*/
static void Controller_reset_input(){
   //NOTHING FOR THIS VERSION...
}
/*--------
Reset procedure
--------*/
void Controller_reset(){
   ctx.M52_nil = _true;
   ctx.M15_nil = _true;
   ctx.M33_nil = _true;
   ctx.M27_nil = _true;
   ctx.M10_nil = _true;
   ctx.M7 = _true;
   Controller_reset_input();
}
/*--------
Step procedure
--------*/
void Controller_step(){
//LOCAL VARIABLES
   _boolean L6;
   _boolean L11;
   _boolean L5;
   _boolean L14;
   _boolean L13;
   _boolean L4;
   _real L35;
   _real L46;
   _real L49;
   _real L45;
   _real L43;
   _real L50;
   _real L42;
   _real L40;
   _real L53;
   _real L39;
   _real L60;
   _boolean L59;
   _real L61;
   _real L58;
   _real L57;
   _real L64;
   _real L62;
   _real L56;
   _real L55;
   _real L38;
   _real L34;
   _real L3;
   _real L67;
   _real L70;
   _real L69;
   _real L68;
   _real L66;
   _real T52;
   _boolean L18;
   _boolean L17;
   _boolean L24;
   _boolean L26;
   _boolean L23;
   _boolean L32;
   _boolean L31;
   _boolean L30;
   _boolean L29;
   _boolean L28;
   _boolean L22;
   _boolean L21;
   _boolean L20;
   _boolean L16;
   _boolean T15;
   _boolean T33;
   _boolean T27;
   _boolean T10;
//CODE
   if (ctx.M7) {
      L6 = _false;
   } else {
      L6 = ctx.M10;
   }
   L11 = (ctx._Co < 20.000000);
   L5 = (L6 || L11);
   if (ctx.M7) {
      L14 = _false;
   } else {
      L14 = ctx.M15;
   }
   L13 = (! L14);
   L4 = (L5 && L13);
   L35 = (1.000000 / 2.000000);
   L46 = (pi / 200.000000);
   L49 = (ctx._Cd - ctx._Cg);
   L45 = (L46 * L49);
   L43 = (0.002000 * L45);
   if (ctx.M7) {
      L50 = 0.000000;
   } else {
      L50 = ctx.M52;
   }
   L42 = (L43 + L50);
   L40 = (ki_teta * L42);
   L53 = (kp_teta * L45);
   L39 = (L40 + L53);
   L60 = (2.000000 * L39);
   L59 = (L60 < 0.000000);
   L61 = (- L60);
   if (L59) {
      L58 = L61;
   } else {
      L58 = L60;
   }
   L57 = (- L58);
   L64 = (ctx._Cd + ctx._Cg);
   L62 = (0.005000 * L64);
   L56 = (L57 + L62);
   L55 = (2.000000 * L56);
   L38 = (L39 + L55);
   L34 = (L35 * L38);
   if (L4) {
      L3 = 10.000000;
   } else {
      L3 = L34;
   }
   Controller_O_u_d(L3);
   L67 = (- 10.000000);
   L70 = (- L39);
   L69 = (L70 + L55);
   L68 = (L35 * L69);
   if (L4) {
      L66 = L67;
   } else {
      L66 = L68;
   }
   Controller_O_u_g(L66);
   T52 = L42;
   L18 = (ctx._Cg >= 90.000000);
   L17 = (L18 || L14);
   L24 = (ctx._Cg <= 10.000000);
   if (ctx.M7) {
      L26 = _false;
   } else {
      L26 = ctx.M27;
   }
   L23 = (L24 || L26);
   if (ctx.M7) {
      L32 = _false;
   } else {
      L32 = ctx.M33;
   }
   L31 = (L18 || L32);
   L30 = (L31 && L13);
   L29 = (L30 || L14);
   L28 = (! L29);
   L22 = (L23 && L28);
   L21 = (L22 || L14);
   L20 = (! L21);
   L16 = (L17 && L20);
   T15 = L16;
   T33 = L30;
   T27 = L22;
   T10 = L4;
   ctx.M52 = T52;
   ctx.M52_nil = _false;
   ctx.M15 = T15;
   ctx.M15_nil = _false;
   ctx.M33 = T33;
   ctx.M33_nil = _false;
   ctx.M27 = T27;
   ctx.M27_nil = _false;
   ctx.M10 = T10;
   ctx.M10_nil = _false;
   ctx.M7 = ctx.M7 && !(_true);
}
