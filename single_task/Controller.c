/********
* ec2c version 0.67
* c file generated for node : Controller
* context   method = STATIC
* ext call  method = PROCEDURES
********/
/* This program needs external declarations */
#define _Controller_EC2C_SRC_FILE
#include "Controller.h"
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
   _real M49;
   _boolean M49_nil;
   _boolean M15;
   _boolean M15_nil;
   _boolean M29;
   _boolean M29_nil;
   _boolean M22;
   _boolean M22_nil;
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
   ctx.M49_nil = _true;
   ctx.M15_nil = _true;
   ctx.M29_nil = _true;
   ctx.M22_nil = _true;
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
   _real L32;
   _real L43;
   _real L46;
   _real L42;
   _real L40;
   _real L47;
   _real L39;
   _real L37;
   _real L50;
   _real L36;
   _real L57;
   _boolean L56;
   _real L58;
   _real L55;
   _real L54;
   _real L61;
   _real L59;
   _real L53;
   _real L52;
   _real L35;
   _real L31;
   _real L3;
   _real L64;
   _real L67;
   _real L66;
   _real L65;
   _real L63;
   _real T49;
   _boolean L19;
   _boolean L21;
   _boolean L18;
   _boolean L17;
   _boolean L26;
   _boolean L28;
   _boolean L25;
   _boolean L24;
   _boolean L23;
   _boolean L16;
   _boolean T15;
   _boolean T29;
   _boolean T22;
   _boolean T10;
//CODE
   if (ctx.M7) {
      L6 = _false;
   } else {
      L6 = ctx.M10;
   }
   L11 = (ctx._Co < 5.000000); // distance for obstacle detection, default = 20
   L5 = (L6 || L11);
   if (ctx.M7) {
      L14 = _false;
   } else {
      L14 = ctx.M15;
   }
   L13 = (! L14);
   L4 = (L5 && L13);
   L32 = (1.000000 / 2.000000);
   L43 = (pi / 200.000000);
   L46 = (ctx._Cd - ctx._Cg);
   L42 = (L43 * L46);
   L40 = (0.002000 * L42);
   if (ctx.M7) {
      L47 = 0.000000;
   } else {
      L47 = ctx.M49;
   }
   L39 = (L40 + L47);
   L37 = (ki_teta * L39);
   L50 = (kp_teta * L42);
   L36 = (L37 + L50);
   L57 = (2.000000 * L36);
   L56 = (L57 < 0.000000);
   L58 = (- L57);
   if (L56) {
      L55 = L58;
   } else {
      L55 = L57;
   }
   L54 = (- L55);
   L61 = (ctx._Cd + ctx._Cg);
   L59 = (0.005000 * L61);
   L53 = (L54 + L59);
   L52 = (2.000000 * L53);
   L35 = (L36 + L52);
   L31 = (L32 * L35);
   if (L4) {
      L3 = 0.100000;
   } else {
      L3 = L31;
   }
   Controller_O_u_d(L3);
   L64 = (- 0.100000);
   L67 = (- L36);
   L66 = (L67 + L52);
   L65 = (L32 * L66);
   if (L4) {
      L63 = L64;
   } else {
      L63 = L65;
   }
   Controller_O_u_g(L63);
   T49 = L39;
   L19 = (ctx._Cg >= 90.000000);
   if (ctx.M7) {
      L21 = _false;
   } else {
      L21 = ctx.M22;
   }
   L18 = (L19 || L21);
   L17 = (L18 && L13);
   L26 = (ctx._Cg <= 10.000000);
   if (ctx.M7) {
      L28 = _false;
   } else {
      L28 = ctx.M29;
   }
   L25 = (L26 || L28);
   L24 = (L25 && L13);
   L23 = (L24 && L17);
   L16 = (L17 && L23);
   T15 = L16;
   T29 = L24;
   T22 = L17;
   T10 = L4;
   ctx.M49 = T49;
   ctx.M49_nil = _false;
   ctx.M15 = T15;
   ctx.M15_nil = _false;
   ctx.M29 = T29;
   ctx.M29_nil = _false;
   ctx.M22 = T22;
   ctx.M22_nil = _false;
   ctx.M10 = T10;
   ctx.M10_nil = _false;
   ctx.M7 = ctx.M7 && !(_true);
}
